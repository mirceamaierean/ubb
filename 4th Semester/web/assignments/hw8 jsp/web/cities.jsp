<%@ page import="web.domain.City" %>
<%@ page import="java.util.List" %>
<html>
<head>
    <title>Cities</title>
    <link rel="stylesheet" type="text/css" href="./style.css">
    <script>
        let selectedCities = [];

        function showNeighbors(cityId, cityName) {
            // Add selected city to the history
            if (selectedCities.length === 0 || selectedCities[selectedCities.length - 1].id !== cityId) {
                selectedCities.push({id: cityId, name: cityName});
            }
            updateSelectedCities();
            saveSelectedCities();
            cityName
            fetch('CityController?cityId=' + cityId + '&=' + encodeURIComponent(cityName), {
                headers: {
                    'X-Requested-With': 'XMLHttpRequest'
                }
            })
                .then(response => response.json())
                .then(data => {
                    let neighborsList = document.getElementById('neighbors');
                    neighborsList.innerHTML = '';
                    if (data.length > 0) {
                        let initialCities = document.getElementById('initial-cities');
                        initialCities.style.display = 'none';
                        data.forEach(neighbor => {
                            let li = document.createElement('li');
                            let a = document.createElement('a');
                            a.href = '#';
                            a.innerText = neighbor.name;
                            a.onclick = function() { showNeighbors(neighbor.id, neighbor.name); return false; };
                            li.appendChild(a);
                            neighborsList.appendChild(li);
                        });
                    } else {
                        let li = document.createElement('li');
                        li.innerText = 'No neighbors found.';
                        neighborsList.appendChild(li);
                    }
                })
                .catch(error => console.error('Error fetching neighbors:', error));
        }

        function updateSelectedCities() {
            let selectedCitiesList = document.getElementById('selected-cities');
            selectedCitiesList.innerHTML = '';
            selectedCities.forEach((city, index) => {
                let li = document.createElement('li');
                let a = document.createElement('a');
                a.href = '#';
                a.innerText = city.name;
                a.onclick = function() {
                    // remove all the cities after the selected city
                    selectedCities = selectedCities.slice(0, index + 1);
                    updateSelectedCities();
                    saveSelectedCities();
                }
                li.appendChild(a);
                selectedCitiesList.appendChild(li);
            });
        }

        function finishJourney() {
            fetch('CityController', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded'
                },
                body: 'selectedCities=' + selectedCities.map(city => city.id).join('_')
            })
                .then(response => {
                    if (response.ok) {
                        document.getElementById('finish-button').style.display = 'none';
                        document.getElementById('start-new-journey').style.display = 'block';
                        document.getElementById('neighbors').innerHTML = '<li>Select a city to see its neighbors.</li>';
                        displayFinishedJourney();
                        selectedCities = [];
                        updateSelectedCities();
                        saveSelectedCities();
                    } else {
                        console.error('Error finishing journey');
                    }
                })
                .catch(error => console.error('Error finishing journey:', error));
        }

        function startNewJourney() {
            document.getElementById('start-new-journey').style.display = 'none';
            document.getElementById('finish-button').style.display = 'block';
            document.getElementById('initial-cities').style.display = 'block';
            document.getElementById('selected-cities').innerHTML = '';
            document.getElementById('finished-journey').innerHTML = '';
            selectedCities = [];
            saveSelectedCities();
        }

        function displayFinishedJourney() {
            let finishedJourneyList = document.getElementById('finished-journey');
            finishedJourneyList.innerHTML = '';
            selectedCities.forEach(city => {
                let li = document.createElement('li');
                li.innerText = city.name;
                finishedJourneyList.appendChild(li);
            });
        }

        function saveSelectedCities() {
            localStorage.setItem('selectedCities', JSON.stringify(selectedCities));
        }

        function loadSelectedCities() {
            const savedCities = localStorage.getItem('selectedCities');
            if (savedCities) {
                selectedCities = JSON.parse(savedCities);
                updateSelectedCities();
            }
        }

        window.onload = function() {
            loadSelectedCities();
        }
    </script>
</head>
<body>
<header>
    <h1>Transportation Route Planner</h1>
</header>
<div class="container">
    <h2>Visited Cities</h2>
    <ul id="selected-cities">
        <!-- Selected cities will be displayed here -->
    </ul>

    <button id="finish-button" onclick="finishJourney()">Finish Journey</button>
    <form method="post" action="StartTravelController">
        <button id="start-new-journey" style="display:none;" onclick="startNewJourney()">Start New Journey</button>
    </form>

    <h2>Cities</h2>
    <ul id="initial-cities">
        <%
            List<City> cities = (List<City>) request.getAttribute("cities");
            if (cities != null) {
                for (City city : cities) {
        %>
        <li><a href="#" onclick="showNeighbors(<%= city.getId() %>, '<%= city.getName() %>'); return false;"><%= city.getName() %></a></li>
        <%
                }
            }
        %>
    </ul>

    <h2>Neighbors</h2>
    <ul id="neighbors">
        <li>Select a city to see its neighbors.</li>
    </ul>

    <h2>Finished Journey</h2>
    <ul id="finished-journey">
        <!-- Finished journey cities will be displayed here -->
    </ul>
</div>
</body>
</html>
