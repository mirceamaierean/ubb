<?php
session_start();
if (!isset($_SESSION['username'])) {
    header('Location: login.php');
    die();
}
$username = $_SESSION['username'];

if (isset($_POST['returnButton'])) {
    header('Location: home.php');
    die();
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>All rooms</title>
    <link href="style.css" rel="stylesheet">
</head>

<body>
    <div class="container text-center" id="viewRoomsDiv">
        <div class="container" id="showRooms">
            <h3>All rooms:</h3>
            <table class="roomtable table">
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Hotel name</th>
                        <th>Room number</th>
                        <th>Category</th>
                        <th>Price</th>
                        <th>Book Room</th>
                    </tr>
                </thead>
                <tbody>
                </tbody>
            </table>
        </div>
        <div id="buttons" class="container text-center">
            <button type="button" id="previousButton" class="btn btn-primary mb-1">Previous</button>
            <button id="nextButton" type="button" class="btn btn-primary mb-1">Next</button>
            <div class="flex-container">
                <div id="filterByCategory" class="mb-3">
                    <label for="categoryInputFilter" class="form-label">Category: </label>
                    <input type="text" id="categoryInputFilter" class="form-control mb-1">
                    <button id="filterByCategoryButton" type="button" class="btn btn-primary">Filter by category</button>
                </div>
                <div id="filterByPrice" class="mb-3">
                    <label for="priceInputFilter" class="form-label">Price: </label>
                    <input type="text" id="priceInputFilter" class="form-control mb-1">
                    <button id="filterByPriceButton" type="button" class="btn btn-primary mb-1">Filter by price</button>
                </div>
            </div>
            <form method="post">
                <input id="returnButton" type="submit" class="btn btn-primary mb-1" name="returnButton" value="Return to main page">
            </form>
        </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="rooms_script.js"></script>
</body>

</html>