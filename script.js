const THEME_STORAGE_KEY = "arduino-collection-theme";
const mql = window.matchMedia("(prefers-color-scheme: dark)");

const projectsGrid = document.getElementById("projectsGrid");
const content = document.querySelector(".content");
const sidebar = document.getElementById("previewSidebar");
const sidebarToggle = document.getElementById("sidebarToggle");
const sidebarTitle = document.getElementById("sidebarTitle");
const sidebarSubtext = document.getElementById("sidebarSubtext");
const previewFrame = document.getElementById("previewFrame");
const sidebarOpenLink = document.getElementById("sidebarOpenLink");
const themeButtons = Array.from(document.querySelectorAll("[data-theme-option]"));

let currentThemeSetting = localStorage.getItem(THEME_STORAGE_KEY) || "auto";
let selectedProjectKey = null;

function asPath(folder, file) {
  return encodeURI(`${folder}/${file}`);
}

function getTinkercadEmbedUrl(url) {
  if (!url) {
    return "";
  }
  if (url.includes("/embed/")) {
    return url;
  }
  const match = url.match(/tinkercad\.com\/things\/([A-Za-z0-9]+)/i);
  if (!match) {
    return url;
  }
  return `https://www.tinkercad.com/embed/${match[1]}?editbtn=1`;
}

function setSidebarOpen(open) {
  sidebar.classList.toggle("is-open", open);
  content.classList.toggle("sidebar-closed", !open);
  sidebarToggle.setAttribute("aria-expanded", String(open));
}

function resolveTheme(setting) {
  if (setting === "auto") {
    return mql.matches ? "dark" : "day";
  }
  return setting;
}

function applyTheme(setting) {
  const resolved = resolveTheme(setting);
  document.documentElement.dataset.theme = resolved;
  currentThemeSetting = setting;

  for (const btn of themeButtons) {
    btn.classList.toggle("is-active", btn.dataset.themeOption === setting);
  }
}

function updateSelectedTileUI() {
  const tiles = document.querySelectorAll(".project-tile");
  for (const tile of tiles) {
    tile.classList.toggle("is-selected", tile.dataset.key === selectedProjectKey);
  }
}

function openInSidebar(project) {
  selectedProjectKey = project.key;
  updateSelectedTileUI();
  setSidebarOpen(true);

  if (!project.tinkercad) {
    sidebarTitle.textContent = "Tinkercad Preview";
    sidebarSubtext.textContent = `${project.name}: Tinkercad link is not available for this project.`;
    previewFrame.src = "about:blank";
    sidebarOpenLink.classList.add("disabled");
    sidebarOpenLink.href = "#";
    return;
  }

  sidebarTitle.textContent = `${project.name} Preview`;
  sidebarSubtext.textContent = "If this page blocks embedding, use Open In New Tab.";
  previewFrame.src = getTinkercadEmbedUrl(project.tinkercad);
  sidebarOpenLink.classList.remove("disabled");
  sidebarOpenLink.href = project.tinkercad;
}

function closeAllMenus(except) {
  const menus = document.querySelectorAll(".menu");
  for (const menu of menus) {
    if (menu !== except) {
      menu.removeAttribute("open");
    }
  }
}

function buildTile(project) {
  const tile = document.createElement("article");
  tile.className = "project-tile";
  tile.dataset.key = project.key;

  const codeHref = asPath(project.folder, project.codeFile);

  tile.innerHTML = `
    <div class="project-head">
      <h3 class="project-name">${project.name}</h3>
      <p class="project-desc">${project.description}</p>
    </div>
    <div class="project-actions">
      <a class="btn" href="${codeHref}" download target="_blank" rel="noopener noreferrer">Download Code</a>
      <a class="btn" href="${codeHref}" target="_blank" rel="noopener noreferrer">View Code</a>
      <details class="menu">
        <summary class="menu-btn">Open Tinkercad</summary>
        <div class="menu-panel">
          <button type="button" class="menu-item" data-open-newtab="true">Open in New Tab</button>
          <button type="button" class="menu-item" data-sidebar-open="true">Open in Sidebar</button>
        </div>
      </details>
    </div>
  `;

  const menu = tile.querySelector(".menu");
  const openInNewTabBtn = tile.querySelector("[data-open-newtab]");
  const openSidebarBtn = tile.querySelector("[data-sidebar-open]");

  menu.addEventListener("toggle", () => {
    if (menu.open) {
      closeAllMenus(menu);
    }
  });

  openInNewTabBtn.addEventListener("click", () => {
    menu.removeAttribute("open");
    if (project.tinkercad) {
      window.open(project.tinkercad, "_blank", "noopener,noreferrer");
      return;
    }
    openInSidebar(project);
  });

  openSidebarBtn.addEventListener("click", () => {
    menu.removeAttribute("open");
    openInSidebar(project);
  });

  return tile;
}

function renderProjects(projects) {
  projectsGrid.innerHTML = "";
  const sortedProjects = [...projects].sort((a, b) => a.name.localeCompare(b.name));
  for (const project of sortedProjects) {
    projectsGrid.appendChild(buildTile(project));
  }
}

function renderDataError(message) {
  projectsGrid.innerHTML = "";
  const box = document.createElement("article");
  box.className = "project-tile";
  box.innerHTML = `
    <div class="project-head">
      <h3 class="project-name">Data Load Error</h3>
      <p class="project-desc">${message}</p>
    </div>
  `;
  projectsGrid.appendChild(box);
}

function attachEvents() {
  document.addEventListener("click", (event) => {
    const menu = event.target.closest(".menu");
    if (!menu) {
      closeAllMenus(null);
    }
  });

  sidebarToggle.addEventListener("click", () => {
    const willOpen = !sidebar.classList.contains("is-open");
    setSidebarOpen(willOpen);
  });

  for (const btn of themeButtons) {
    btn.addEventListener("click", () => {
      const option = btn.dataset.themeOption;
      localStorage.setItem(THEME_STORAGE_KEY, option);
      applyTheme(option);
    });
  }

  mql.addEventListener("change", () => {
    if (currentThemeSetting === "auto") {
      applyTheme("auto");
    }
  });
}

function init() {
  const payload = window.ARDUINO_PROJECTS_DATA;
  const projects = payload?.projects;

  if (!Array.isArray(projects) || projects.length === 0) {
    renderDataError("No project data available. Generate projects-data.js from data.ods.");
  } else {
    renderProjects(projects);
  }

  applyTheme(currentThemeSetting);
  attachEvents();
  setSidebarOpen(sidebar.classList.contains("is-open"));
}

init();
