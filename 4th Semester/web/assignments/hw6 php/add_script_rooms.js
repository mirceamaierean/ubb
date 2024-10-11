$(document).ready(() => {
  $("#insertLogButton").click(() => {
    const urlParams = new URLSearchParams(window.location.search);
    console.log("url params", urlParams);
    const hotel_id = urlParams.get("hotel_id");
    if (!hotel_id || isNaN(hotel_id)) {
      alert("Hotel id is not valid!");
      return;
    }

    const room_number = $("#severityField").val();
    if (isNaN(room_number.trim())) {
      alert("Room number is not valid!");
      return;
    }

    const category = $("#typeField1").val().trim();
    if (category.length === 0) {
      alert("Category is not valid!");
      return;
    }

    const price = $("#severityField1").val().trim();

    if (isNaN(price.trim())) {
      alert("Price is not valid!");
      return;
    }
    $.ajax({
      type: "GET",
      url: "http://localhost:80/hw/DBUtils.php",
      data: {
        action: "insertRoom",
        hotel_id: hotel_id,
        room_number: room_number,
        category: category,
        price: price,
      },
      success: (data) => {
        let res = JSON.parse(data);
        if (res === 0) {
          alert("Room could not be added!");
        } else {
          $(".form-control").val("");
          alert("Room added successfully!");
        }
      },
    });
  });
});
