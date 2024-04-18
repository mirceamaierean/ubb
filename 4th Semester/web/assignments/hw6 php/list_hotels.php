<?php
session_start();
if (isset($_POST['returnButton'])) {
    header('Location: home.php');
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>All hotels</title>
    <link href="style.css" rel="stylesheet">
</head>

<body>
    <div class="container text-center">
        <div class="container">
            <h3>All hotels:</h3>
            <table class="logTable table">
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Name</th>
                        <th>Address</th>
                        <th>Add Room</th>
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
                <div id="filterByName" class="mb-3">
                    <label for="nameInputFilter" class="form-label">Name:</label>
                    <input type="text" id="nameInputFilter" class="form-control mb-1">
                    <button id="filterByNameButton" type="button" class="btn btn-primary">Filter by name</button>
                </div>
                <div id="filterByAddress" class="mb-3">
                    <label for="addressInputFilter" class="form-label">Address:</label>
                    <input type="text" id="addressInputFilter" class="form-control mb-1">
                    <button id="filterByAddressButton" type="button" class="btn btn-primary">Filter by address</button>
                </div>
            </div>
            <form method="post">
                <input id="returnButton" type="submit" class="btn btn-primary mb-1" name="returnButton" value="Return to main page">
            </form>
        </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="hotels_script.js"></script>
</body>

</html>