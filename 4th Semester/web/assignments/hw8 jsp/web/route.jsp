<%@ page import="web.domain.*" %>
<%@ page import="java.util.List" %>
<html>
<head>
    <title>Choose Route</title>
    <link rel="stylesheet" type="text/css" href="./style.css">
</head>
<body>
<header>
    <h1>Transportation Route Planner</h1>
</header>
<div class="container">
    <c:if test="${not empty sessionScope.user}">
        <p>Welcome, ${sessionScope.user.username}!</p>
        <form method="post" action="logout">
            <button type="submit">Logout</button>
        </form>
    </c:if>
    <h2>Current Station: ${currentCity.name}</h2>
    <h3>Neighboring Cities:</h3>
    <ul>
        <c:forEach var="neighbor" items="${neighbors}">
            <li><a href="TravelController?cityId=${neighbor.id}">${neighbor.name}</a></li>
        </c:forEach>
    </ul>
    <form method="post" action="route">
        <button type="submit" name="action" value="finalize">Finalize Route</button>
        <button type="submit" name="action" value="reset">Reset Route</button>
    </form>
    <h3>Route so far:</h3>
    <ul>
        <%
            List<City> cities = (List<City>) request.getAttribute("cities");
            for (City city : cities) {
        %>
        <li><a href="TravelController?cityId=<%= city.getId() %>"><%= city.getName() %></a></li>
        <%
            }
        %>
    </ul>
</div>
</body>
</html>
