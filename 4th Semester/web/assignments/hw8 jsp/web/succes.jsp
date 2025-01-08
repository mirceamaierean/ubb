<%@ page import="web.domain.City" %>
<%@ page import="java.util.List" %>
<html>
<head>
    <title>Start Travel</title>
    <link rel="stylesheet" type="text/css" href="./style.css">
</head>
<body>
<header>
    <h1>Transportation Route Planner</h1>
</header>
<div class="container">
    <h2>Start a New Travel</h2>
    <form method="post" action="StartTravelController">
        <button type="submit">Start Travel</button>
    </form>
</div>
</body>
</html>
