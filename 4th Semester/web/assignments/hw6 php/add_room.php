<?php
session_start();
if (!isset($_SESSION['username'])) {
    header('Location: login.php');
}
if (isset($_POST['returnButton'])) {
    header('Location: home.php');
}
if (isset($_POST['viewAllButton'])) {
    header('Location: list_rooms.php');
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Add a room</title>
    <link href="style.css" rel="stylesheet">
</head>

<body>
    <div class="container text-center" id="addFormDiv">
        <div id="addForm">
            <h5>Add a room</h5>
            <div class="form-group">
                <label for="severityField">Room Number:</label>
                <input type="text" id="severityField" class="form-control">
            </div>
            <div class="form-group">
                <label for="typeField1">Category:</label>
                <input type="text" id="typeField1" class="form-control">
            </div>
            <div class="form-group">
                <label for="severityField1">Price:</label>
                <input type="text" id="severityField1" class="form-control">
            </div>
            <button id="insertLogButton" class="btn btn-primary mb-1">Add room</button>
        </div>
        <br>
        <form method="post">
            <input type="submit" class="btn btn-primary mb-1" name="viewAllButton" value="View all rooms">
            <input type="submit" class="btn btn-primary mb-1" name="returnButton" value="Return to main page">
        </form>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="add_script_rooms.js"></script>
</body>

</html>