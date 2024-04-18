<?php
// Check if the ID parameter is set
if (isset($_POST['editId'])) {
    // Get the ID value
    $id = $_POST['editId'];
    echo $id;
}

if (isset($_POST['returnButton'])) {
    header('Location: home.php');
}
if (isset($_POST['viewAllButton'])) {
    header('Location: reservations.php');
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Edit reservation</title>
    <link href="style.css" rel="stylesheet">
</head>

<body>
    <div class="container text-center" id="addFormDiv">
        <div id="addForm">
            <h5>Edit a reservation</h5>
            <div class="form-group">
                <label for="startDate" class="form-label">Start Date:</label>
                <input type="date" id="startDate" class="form-control">
            </div>
            <div class="form-group">
                <label for="endDate" class="form-label">End Date:</label>
                <input type="date" id="endDate" class="form-control">
            </div>
            <button id="editButton" class="btn btn-primary mb-1">Edit</button>
        </div>
        <br>
        <form method="post">
            <input type="submit" class="btn btn-primary mb-1" name="viewAllButton" value="View all reservations">
            <input type="submit" class="btn btn-primary mb-1" name="returnButton" value="Return to main page">
        </form>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="add_script_reservations.js"></script>

    <script>
        // set the value of the startDate and endDate fields
        const urlParams = new URLSearchParams(window.location.search);

        const start_date = urlParams.get('start_date');
        const end_date = urlParams.get('end_date');

        $('#startDate').val(start_date);
        $('#endDate').val(end_date);

        $('#editButton').click(() => {
            let start_date = $('#startDate').val();
            let end_date = $('#endDate').val();
            let id = urlParams.get('id');

            if (isNaN(id)) {
                alert("Invalid ID!");
                return;
            }

            if (start_date && end_date && start_date < end_date) {
                $.ajax({
                    type: 'GET',
                    url: "http://localhost:80/hw/DBUtils.php",
                    data: {
                        action: 'editReservation',
                        id: id,
                        start_date: start_date,
                        end_date: end_date,
                    },
                    success: (data) => {
                        let res = JSON.parse(data);
                        if (res === 0) {
                            alert("Reservation could not be edited!");
                        } else {
                            $('.form-control').val("");
                            alert("Reservation edited successfully!");
                        }
                    }
                })
            } else {
                alert("Please enter valid data in all fields!");
            }
        })
    </script>
</body>

</html>