package web.model;

import web.domain.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBManager {
    private Connection con;

    public DBManager() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/travel", "root", "");
        } catch (Exception ex) {
            System.out.println("Error connecting to the database: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public User authenticate(String username, String password) {
        User u = null;
        String query = "SELECT * FROM users WHERE username = ? AND password = ?";
        try (PreparedStatement pstmt = con.prepareStatement(query)) {
            pstmt.setString(1, username);
            pstmt.setString(2, password);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    u = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return u;
    }

    public List<City> getAllCities() throws SQLException {
        List<City> cities = new ArrayList<>();
        String query = "SELECT * FROM cities";
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(query)) {
            while (rs.next()) {
                cities.add(new City(rs.getInt("id"), rs.getString("name")));
            }
        }
        return cities;
    }

    public void addTravel(Travel travel) throws SQLException {
        String query = "INSERT INTO travels (user_id, start_time) VALUES (?, ?)";
        try (PreparedStatement stmt = con.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            stmt.setInt(1, travel.getUserId());
            stmt.setTimestamp(2, Timestamp.valueOf(travel.getStartTime()));
            stmt.executeUpdate();

            try (ResultSet generatedKeys = stmt.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    travel.setId(generatedKeys.getInt(1));
                }
            }
        }
    }

    // get current travel for user. it is the one that has the most recent start_time
    public Travel getCurrentTravel(int userId) throws SQLException {
        Travel travel = null;
        String query = "SELECT * FROM travels WHERE user_id = ? ORDER BY start_time DESC LIMIT 1";
        try (PreparedStatement stmt = con.prepareStatement(query)) {
            stmt.setInt(1, userId);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    travel = new Travel(
                            rs.getInt("id"),
                            rs.getInt("user_id"),
                            rs.getTimestamp("start_time").toLocalDateTime()
                    );
                }
            }
        }
        return travel;
    }

    public List<Travel> getTravelsByUser(int userId) throws SQLException {
        List<Travel> travels = new ArrayList<>();
        String query = "SELECT * FROM travels WHERE user_id = ?";
        try (PreparedStatement stmt = con.prepareStatement(query)) {
            stmt.setInt(1, userId);
            try (ResultSet rs = stmt.executeQuery()) {
                while (rs.next()) {
                    travels.add(new Travel(
                            rs.getInt("id"),
                            rs.getInt("user_id"),
                            rs.getTimestamp("start_time").toLocalDateTime()
                    ));
                }
            }
        }
        return travels;
    }


    public String getNameOfCity(int cityId) throws SQLException {
        String query = "SELECT name FROM cities WHERE id = ?";
        try (PreparedStatement stmt = con.prepareStatement(query)) {
            stmt.setInt(1, cityId);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getString("name");
                }
            }
        }
        return null;
    }
    public List<City> getNeighbors(int cityId) throws SQLException {
        List<City> neighbors = new ArrayList<>();
        // get from the station all the records, where one of city1 or city2 is the cityId
        String query = "SELECT * FROM station WHERE station.city1_id = ? OR station.city2_id = ?";

        try (PreparedStatement stmt = con.prepareStatement(query)) {
            stmt.setInt(1, cityId);
            stmt.setInt(2, cityId);
            try (ResultSet rs = stmt.executeQuery()) {
                while (rs.next()) {
                    int city1Id = rs.getInt("city1_id");
                    int city2Id = rs.getInt("city2_id");

                    if (city1Id == cityId) {
                        neighbors.add(new City(city2Id, getNameOfCity(city2Id)));
                    } else {
                        neighbors.add(new City(city1Id, getNameOfCity(city1Id)));
                    }
                }
            }

        }
        return neighbors;
    }

    public void endTravel(int travelId) throws SQLException {
        String query = "UPDATE travels SET ended = true WHERE id = ?";
        try (PreparedStatement stmt = con.prepareStatement(query)) {
            stmt.setInt(1, travelId);
            stmt.executeUpdate();
        }
    }
    public void addPins(int travelId, List<String> cities) throws SQLException {
        String query = "INSERT INTO pin (travel_id, city_id, step_number) VALUES (?, ?, ?)";
        try (PreparedStatement stmt = con.prepareStatement(query)) {
            for (int i = 0; i < cities.size(); i++) {
                stmt.setInt(1, travelId);
                stmt.setInt(2, Integer.parseInt(cities.get(i)));
                stmt.setInt(3, i + 1);
                stmt.addBatch();
            }
            stmt.executeBatch();
        }
    }

    public void addPin(int travelId, int cityId, int stepNumber) throws SQLException {
        String query = "INSERT INTO pin (travel_id, city_id, step_number) VALUES (?, ?, ?)";
        try (PreparedStatement stmt = con.prepareStatement(query)) {
            stmt.setInt(1, travelId);
            stmt.setInt(2, cityId);
            stmt.setInt(3, stepNumber);
            stmt.executeUpdate();
        }
    }


    // Ensure to close the connection when the application shuts down
    public void close() {
        try {
            if (con != null && !con.isClosed()) {
                con.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
