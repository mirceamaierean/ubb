<?php
session_start();
if (!isset($_SESSION['username'])) {
    header('Location: login.php');
}
if (isset($_POST['returnButton'])) {
    header('Location: home.php');
}
if (isset($_POST['viewAllButton'])) {
    header('Location: list_hotels.php');
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="style.css">
    <title>Add a hotel</title>
</head>

<body>
    <div class="container-small text-center" id="addFormDiv">
        <div id="addForm">
            <br></br>
            <h1>Add a hotel</h1>
            <br></br>
            <div class="mb-1"><label for="typeField" class="form-label">Name: </label><input type="text" id="typeField" class="form-control"></div>
            <div class="mb-1"><label for="severityField" class="form-label">Address: </label><input type="text" id="severityField" class="form-control"></div>
            <button id="insertLogButton" type="button" class="btn btn-primary mb-1">Add hotel</button>
        </div>
        <br></br>
        <form method="post">
            <input type="submit" class="btn btn-primary mb-1" name="viewAllButton" value="View all hotels">
            <input type="submit" class="btn btn-primary mb-1" name="returnButton" value="Return to main page">
        </form>
    </div>
    </div>
</body>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
<script src="add_script.js"></script>

</html>