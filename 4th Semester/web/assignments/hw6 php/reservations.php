<?php
session_start();
if (isset($_SESSION['username'])) {
    $username = $_SESSION['username'];
    echo "<script>var username = '" . $username . "';</script>";
} else {
    header('Location: login.php');
    die();
}

?>


<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>All your reservations</title>
    <link rel="stylesheet" href="style.css">
</head>

<body>
    <div class="container text-center" id="viewReservationsDiv">
        <div class="container" id="showReservations">
            <h3>All reservations:</h3>
            <table class="reservationtable table">
                <thead>
                    <tr>
                        <th id="clickable-header">ID</th>
                        <th>Room Number</th>
                        <th>Hotel Name</th>
                        <th>Start Date</th>
                        <th>End Date</th>
                        <th>Edit Button</th>
                        <th>Delete Button</th>
                    </tr>
                </thead>
                <tbody>
                </tbody>
            </table>
        </div>
        <div id="buttons" class="container text-center">
            <button type="button" id="previousButton" class="btn btn-primary mb-1">Previous</button>
            <button id="nextButton" type="button" class="btn btn-primary mb-1">Next</button>
            <button id="returnButton" type="button" class="btn btn-primary mb-1">Return</button>
        </div>
    </div>
</body>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
<script src="reservations.js"></script>

</html>