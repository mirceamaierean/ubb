let currentPage = 0;

const insertData = (newBody, data) => {
  if (currentPage === 0) {
    $("#previousButton").attr("disabled", true);
  }
  let result = JSON.parse(data);
  let numberOfPages = Math.ceil(result.length / 4);
  for (let log of result) {
    let newRow = newBody.insertRow();
    if (result.indexOf(log) >= 4 * currentPage) {
      for (let index of [
        "id",
        "room_number",
        "hotel_name",
        "start_date",
        "end_date",
      ]) {
        let newCol = newRow.insertCell();
        let newText = document.createTextNode(log[index]);
        newCol.appendChild(newText);
      }
      // Add a new cell with the "Edit" button
      let newCol = newRow.insertCell();
      let editButton = document.createElement("button");
      editButton.textContent = "Edit";
      editButton.onclick = () => {
        window.location.href = `edit_reservation.php?id=${log["id"]}&start_date=${log["start_date"]}&end_date=${log["end_date"]}`;
      };
      newCol.appendChild(editButton);

      // Add a new cell with the "Remove" button
      newCol = newRow.insertCell();
      let removeButton = document.createElement("button");
      removeButton.textContent = "Remove";
      removeButton.onclick = () => {
        if (removeReservation(log["id"])) newRow.remove();
      };
      newCol.appendChild(removeButton);

      newBody.append(newRow);
    }
    if (result.indexOf(log) >= 4 * currentPage + 3) {
      break;
    }
  }
  if (numberOfPages === 0) {
    $("#nextButton").attr("disabled", true);
  } else {
    if (currentPage === numberOfPages - 1) {
      $("#nextButton").attr("disabled", true);
    } else {
      $("#nextButton").attr("disabled", false);
    }
  }
};

function removeReservation(id) {
  let confirmDelete = confirm(
    "Are you sure you want to delete this reservation?"
  );
  if (!confirmDelete) return false;
  $.ajax({
    type: "GET",
    url: "http://localhost:80/hw/DBUtils.php",
    data: { action: "deleteReservation", id: id },
    success: function (data) {
      return true;
    },
    error: function () {
      alert("Could not delete the reservation!");
      return false;
    },
  });
}

function doSomethingWithUserId(user_id) {
  let body = $(".reservationtable tbody").eq(0);
  let newBody = document.createElement("tbody");
  $.ajax({
    type: "GET",
    url: "http://localhost:80/hw/DBUtils.php",
    data: { action: "getReservationByUserId", user_id: user_id },
    success: (data) => {
      insertData(newBody, data);
    },
  });
  body.replaceWith(newBody);
}

$(document).ready(() => {
  $.ajax({
    type: "GET",
    url: "http://localhost:80/hw/DBUtils.php",
    data: { action: "selectIdByUsername", username: username },
    success: function (result) {
      var response = JSON.parse(result);
      var user_id = parseInt(response[0].id, 10);
      doSomethingWithUserId(user_id);
    },
  });

  $("#previousButton").click(() => {
    if (currentPage > 0) {
      currentPage--;
      if (currentPage === 0) {
        $("#previousButton").attr("disabled", true);
      }
    }
    showCorrectHotels();
  });

  $("#nextButton").click(() => {
    $("#previousButton").attr("disabled", false);
    currentPage++;
    showCorrectHotels();
  });

  $("#returnButton").click(() => {
    window.location.href = "home.php";
  });
});
