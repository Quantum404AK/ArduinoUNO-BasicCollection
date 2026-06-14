#!/usr/bin/env python3
"""Generate projects-data.js from data.ods for the website."""

from __future__ import annotations

import json
import re
import zipfile
from datetime import datetime, timezone
from pathlib import Path
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parent.parent
ODS_PATH = ROOT / "data.ods"
OUTPUT_PATH = ROOT / "projects-data.js"

TABLE_NS = "urn:oasis:names:tc:opendocument:xmlns:table:1.0"
TEXT_NS = "urn:oasis:names:tc:opendocument:xmlns:text:1.0"
XLINK_NS = "http://www.w3.org/1999/xlink"

NS = {
    "table": TABLE_NS,
    "text": TEXT_NS,
}

EXCLUDED_FOLDERS = {"auto door pir"}


def normalize_key(value: str) -> str:
    return re.sub(r"[^a-z0-9]", "", value.lower())


def flatten_text(node: ET.Element) -> str:
    return "".join(node.itertext()).strip()


def extract_cell(cell: ET.Element) -> dict[str, str]:
    text_value = flatten_text(cell)
    link_node = cell.find(".//text:a", NS)
    href = ""
    if link_node is not None:
        href = link_node.get(f"{{{XLINK_NS}}}href", "").strip()
    return {"text": text_value, "href": href}


def discover_code_files() -> list[dict[str, str]]:
    items = []
    for folder in sorted(ROOT.iterdir()):
        if not folder.is_dir():
            continue
        if folder.name.startswith("."):
            continue
        if folder.name.lower() in EXCLUDED_FOLDERS:
            continue
        ino_files = sorted(folder.glob("*.ino"))
        if not ino_files:
            continue
        code = ino_files[0]
        items.append(
            {
                "folder": folder.name,
                "codeFile": code.name,
                "key": normalize_key(folder.name),
            }
        )
    return items


def parse_ods_rows() -> list[dict[str, str]]:
    with zipfile.ZipFile(ODS_PATH, "r") as zf:
        raw_xml = zf.read("content.xml")

    root = ET.fromstring(raw_xml)
    table = root.find(".//table:table", NS)
    if table is None:
        return []

    rows = []
    for row in table.findall("table:table-row", NS):
        cells = row.findall("table:table-cell", NS)
        if not cells:
            continue

        parsed = [extract_cell(c) for c in cells[:4]]
        while len(parsed) < 4:
            parsed.append({"text": "", "href": ""})

        name = parsed[0]["text"].strip()
        description = parsed[1]["text"].strip()
        tinkercad = (parsed[2]["href"] or parsed[2]["text"]).strip()
        functioning = parsed[3]["text"].strip()

        if name.lower() == "name":
            continue

        if not any([name, description, tinkercad, functioning]):
            repeated = row.get(f"{{{TABLE_NS}}}number-rows-repeated")
            if repeated and int(repeated) > 1000:
                break
            continue

        rows.append(
            {
                "name": name,
                "description": description,
                "tinkercad": tinkercad,
                "functioning": functioning,
                "key": normalize_key(name),
            }
        )
    return rows


def build_projects() -> list[dict[str, str]]:
    code_entries = discover_code_files()
    code_map = {entry["key"]: entry for entry in code_entries}
    ods_rows = parse_ods_rows()
    projects: list[dict[str, str]] = []

    for row in ods_rows:
        code = code_map.get(row["key"])
        if not code:
            continue
        projects.append(
            {
                "key": code["folder"],
                "name": row["name"] or code["folder"],
                "folder": code["folder"],
                "codeFile": code["codeFile"],
                "description": row["description"] or "Arduino UNO project.",
                "tinkercad": row["tinkercad"],
                "functioning": row["functioning"],
            }
        )

    projects.sort(key=lambda item: item["name"].lower())
    return projects


def main() -> None:
    projects = build_projects()
    payload = {
        "generatedAt": datetime.now(timezone.utc).isoformat(),
        "source": "data.ods",
        "projectCount": len(projects),
        "projects": projects,
    }

    output = "window.ARDUINO_PROJECTS_DATA = " + json.dumps(payload, indent=2) + ";\n"
    OUTPUT_PATH.write_text(output, encoding="utf-8")
    print(f"Generated {OUTPUT_PATH} with {len(projects)} projects.")


if __name__ == "__main__":
    main()
