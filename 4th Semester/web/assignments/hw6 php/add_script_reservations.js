function doSomethingWithUserId(user_id) {
  $("#insertLogButton").click(() => {
    const urlParams = new URLSearchParams(window.location.search);
    console.log("url params", urlParams);
    const room_id = urlParams.get("id");
    let start_date = $("#startDate").val();
    let end_date = $("#endDate").val();
    if (start_date < end_date) {
      $.ajax({
        type: "GET",
        url: "http://localhost:80/hw/DBUtils.php",
        data: {
          action: "insertReservation",
          room_id: room_id,
          user_id: user_id,
          start_date: start_date,
          end_date: end_date,
        },
        success: (data) => {
          let res = JSON.parse(data);
          if (res === 0) {
            alert("Reservation could not be added!");
          } else {
            $(".form-control").val("");
            alert("Reservation added successfully!");
          }
        },
      });
    } else {
      alert("Please enter valid data in all fields!");
    }
  });
}

$(document).ready(() => {
  $.ajax({
    type: "GET",
    url: "http://localhost:80/hw/DBUtils.php",
    data: { action: "selectIdByUsername", username: username },
    success: function (result) {
      const response = JSON.parse(result);
      const user_id = parseInt(response[0].id, 10);
      doSomethingWithUserId(user_id);
    },
  });
});
