const menuData = [
  {
    title: "Submenu 1",
    components: ["Component 1", "Component 2", "Component 3"],
  },
  {
    title: "Submenu 2",
    components: ["Component 1", "Component 2", "Component 3", "Component 4"],
  },
  {
    title: "Submenu 3",
    components: [
      "Component 1",
      "Component 2",
      "Component 3",
      "Component 4",
      "Component 5",
    ],
  },
  {
    title: "Submenu 4",
    components: ["Component 1", "Component 2", "Component 3", "Component 4"],
  },
  {
    title: "Submenu 5",
    components: ["Component 1", "Component 2", "Component 3"],
  },
];

const body = document.createElement("body");
document.body = body;

const menuContainer = document.createElement("div");
menuContainer.classList.add("menu");
document.body.appendChild(menuContainer);

menuData.forEach((submenuData) => {
  const submenuDiv = document.createElement("div");
  submenuDiv.classList.add("submenu");

  const title = document.createElement("h3");
  title.textContent = submenuData.title;
  submenuDiv.appendChild(title);

  const componentList = document.createElement("ul");
  submenuData.components.forEach((component) => {
    const componentItem = document.createElement("li");
    componentItem.classList.add("submenu-item");
    componentItem.textContent = component;
    componentList.appendChild(componentItem);
  });

  submenuDiv.appendChild(componentList);
  menuContainer.appendChild(submenuDiv);
});
