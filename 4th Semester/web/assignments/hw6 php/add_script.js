$(document).ready(() => {
  $("#insertLogButton").click(() => {
    let name = $("#typeField").val();
    let address = $("#severityField").val();
    if (name.trim().length > 0 && address.trim().length) {
      $.ajax({
        type: "GET",
        url: "http://localhost:80/hw/DBUtils.php",
        data: {
          action: "insertHotel",
          name: name,
          address: address,
        },
        success: (data) => {
          let res = JSON.parse(data);
          if (res === 0) {
            alert("Hotel could not be added!");
          } else {
            $(".form-control").val("");
            alert("Hotel added successfully!");
          }
        },
      });
    } else {
      alert("Please enter valid data in all fields!");
    }
  });
});
