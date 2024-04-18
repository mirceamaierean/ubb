<?php
session_start();
if (isset($_SESSION['username'])) {
    $username = $_SESSION['username'];
    echo "<script>var username = '" . $username . "';</script>";
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
    <title>Add a reservation</title>
    <link href="style.css" rel="stylesheet">
</head>

<body>
    <div class="container text-center" id="addFormDiv">
        <div id="addForm">
            <h5>Book a room</h5>
            <div class="form-group">
                <label for="startDate" class="form-label">Start Date:</label>
                <input type="date" id="startDate" class="form-control">
            </div>
            <div class="form-group">
                <label for="endDate" class="form-label">End Date:</label>
                <input type="date" id="endDate" class="form-control">
            </div>
            <button id="insertLogButton" class="btn btn-primary mb-1">Add reservation</button>
        </div>
        <br>
        <form method="post">
            <input type="submit" class="btn btn-primary mb-1" name="viewAllButton" value="View all reservations">
            <input type="submit" class="btn btn-primary mb-1" name="returnButton" value="Return to main page">
        </form>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="add_script_reservations.js"></script>
</body>

</html>