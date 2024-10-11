<?php
header('Cache-Control: no-cache, must-revalidate');
require_once 'DBUtils.php';

session_start();

if (isset($_SESSION['username'])) {
    unset($_SESSION['username']);
}

function checkValidPassword(string $username, string $password): bool
{
    $connection = new DBConnection();
    $result = $connection->selectUserByUsername($username);
    if (count($result) == 0)
        return false;
    if ($result[0]["password"] === $password)
        return true;
    return false;
}

if (isset($_POST['loginButton'])) {
    $errors = 0;
    $fields = array("username", "password");
    foreach ($fields as $key => $field)
        if (!isset($_POST[$field]) && empty($_POST[$field]))
            $errors++;

    if ($errors > 0)
        $_SESSION['login-error'] = "Invalid username and/or password! Try again!";
    else {
        $username = $_POST['username'];
        $password = $_POST['password'];
        if (checkValidPassword($username, $password)) {
            $_SESSION['username'] = $username;
            header("Location: home.php");
        } else
            $_SESSION['login-error'] = "Invalid username and/or password! Try again!";
    }
}

if (isset($_POST['indexPage'])) {
    header('Location: index.php');
}

?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Login</title>
</head>

<body>
    <form id="login-form" method="post" action="login.php" class="container-small">
        <div class="form-group">
            <label for="username" class="label">Username:</label>
            <input type="text" class="form-control" id="username" placeholder="Enter username" name="username">
        </div>
        <div class="form-group">
            <label for="password" class="label">Password:</label>
            <input type="password" class="form-control" id="password" placeholder="Enter password" name="password">
        </div>
        <input type="submit" class="btn btn-primary mb-3" name="loginButton" value="Login">
        <input type="submit" class="btn btn-primary" name="indexPage" value="Go to index page">
        <?php
        if (isset($_SESSION['login-error'])) {
            $error = $_SESSION['login-error'];
            echo '<script type="text/javascript">';
            echo 'window.alert("Invalid username and/or password")';
            echo '</script>';
        }
        ?>
    </form>
</body>

</html>

<?php
unset($_SESSION['login-error']);
?>