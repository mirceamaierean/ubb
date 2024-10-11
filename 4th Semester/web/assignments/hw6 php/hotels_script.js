let currentPage = 0;
let showType = "all";
let hotels = [];

const insertData = (newBody) => {
  const startIndex = 4 * currentPage;
  const endIndex = 4 * currentPage + 3;
  for (let i = startIndex; i <= endIndex; i++) {
    let newRow = newBody.insertRow();

    for (let index of ["id", "name", "address"]) {
      let newCol = newRow.insertCell();
      let newText = document.createTextNode(hotels[i][index].toString());
      newCol.appendChild(newText);
    }

    // make a button to redirect to add_hotel.php?id=id
    let newCol = newRow.insertCell();
    let addButton = document.createElement("button");
    addButton.textContent = "+";
    addButton.onclick = () => {
      window.location.href = `add_room.php?hotel_id=${hotels[i]["id"]}`;
    };
    newCol.appendChild(addButton);

    newBody.append(newRow);
  }
};

const showAllHotels = () => {
  let body = $(".logTable tbody").eq(0);
  let newBody = document.createElement("tbody");
  $.ajax({
    type: "GET",
    url: "http://localhost:80/hw/DBUtils.php",
    data: { action: "getAllHotels" },
    success: (data) => {
      hotels = JSON.parse(data);
      insertData(newBody);
    },
  });
  body.replaceWith(newBody);
};

const showHotelByName = (name) => {
  let body = $(".logTable tbody").eq(0);
  currentPage = 0;
  let newBody = document.createElement("tbody");
  $.ajax({
    type: "GET",
    url: "http://localhost:80/hw/DBUtils.php",
    data: { action: "getHotelByName", hotel: name },
    success: (data) => {
      insertData(newBody, data);
    },
  });
  body.replaceWith(newBody);
};

const showHotelByAddr = (addr) => {
  let body = $(".logTable tbody").eq(0);
  currentPage = 0;
  let newBody = document.createElement("tbody");
  $.ajax({
    type: "GET",
    url: "http://localhost:80/hw/DBUtils.php",
    data: { action: "getHotelByAddr", address: addr },
    success: (data) => {
      hotels = JSON.parse(data);
      insertData(newBody);
    },
  });
  body.replaceWith(newBody);
};

const showCorrectHotels = () => {
  switch (showType) {
    case "all":
      showAllHotels();
      break;

    case "name":
      names = $("#nameInputFilter").val().trim();
      if (names.length > 0) showHotelByName(names);
      else {
        showType = "all";
      }
      break;

    case "addr":
      addr = $("#addressInputFilter").val().trim();
      if (addr.length > 0) showHotelByAddr(addr);
      else {
        showType = "all";
      }
      break;
  }
};

const handleNextClick = () => {
  currentPage++;
  if (currentPage === Math.floor((hotels.length - 1) / 4))
    $("#nextButton").attr("disabled", true);
  let body = $(".logTable tbody").eq(0);
  $("#previousButton").attr("disabled", false);
  let newBody = document.createElement("tbody");
  insertData(newBody);
  console.log(currentPage);
  body.replaceWith(newBody);
};

const handlePreviousClick = () => {
  $("#nextButton").attr("disabled", false);
  if (currentPage > 0) currentPage--;
  {
    let body = $(".logTable tbody").eq(0);
    let newBody = document.createElement("tbody");
    insertData(newBody);
    body.replaceWith(newBody);
  }
  if (currentPage === 0) $("#previousButton").attr("disabled", true);
};

const handleFilterByName = () => {};

$(document).ready(() => {
  showAllHotels();

  $("#previousButton").attr("disabled", true);

  $("#filterByName").click(() => {
    currentPage = 0;
    showType = "name";
    showCorrectHotels();
  });

  $("#filterByAddress").click(() => {
    currentPage = 0;
    showType = "addr";
    showCorrectHotels();
  });

  $("#previousButton").click(() => {
    handlePreviousClick();
  });

  $("#nextButton").click(() => {
    handleNextClick();
  });
});
