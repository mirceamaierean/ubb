<?php
session_start();
if (isset($_SESSION['username'])) {
    $username = $_SESSION['username'];
} else {
    header('Location: login.php');
    die();
}
if (isset($_POST['viewAllButton'])) {
    header('Location: list_hotels.php');
}
if (isset($_POST['logoutButton'])) {
    session_unset();
    session_destroy();
    header('Location: login.php');
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>Hotel booking site</title>
    <link rel="stylesheet" href="style.css">
</head>

<body>
    <main>
        <div class="container text-center">
            <h3>Welcome, <?php echo $username; ?>!</h3>
        </div>
        <div class="container text-center" id="index-page">
            <button type="button" class="btn btn-primary btn-block" onclick="location.href='list_hotels.php'">List all hotels</button>
            <button type="button" class="btn btn-primary btn-block" onclick="location.href='list_rooms.php'">List all rooms</button>
            <button type="button" class="btn btn-primary btn-block" onclick="location.href='reservations.php'">My reservations</button>
            <button type="button" class="btn btn-primary" onclick="location.href='add_hotel.php'">Add hotel</button>
            <button type="button" class="btn btn-primary" onclick="location.href='login.php'">Log out</button>
        </div>
    </main>
</body>

</html>