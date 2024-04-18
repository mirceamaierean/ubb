<?php
class DBConnection
{
    private $host = "localhost";
    private $user = "root";
    private $pass = "";
    private $db = "room-booking";
    private $charset = 'utf8';

    private $pdo;
    private $error;

    public function __construct()
    {
        $dsn = "mysql:host=$this->host;dbname=$this->db;charset=$this->charset";
        $opt = array(
            PDO::ATTR_ERRMODE   => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES   => false
        );

        try {
            $this->pdo = new PDO($dsn, $this->user, $this->pass, $opt);
        } // Catch any errors
        catch (PDOException $e) {
            $this->error = $e->getMessage();
            echo "Error connecting to DB: " . $this->error;
        }
    }

    public function getHotelByName($hotel)
    {
        if (!empty($hotel)) {
            $stmt = $this->pdo->prepare("SELECT * FROM hotels WHERE name = ?");
            $stmt->execute([$hotel]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } else {
            http_response_code(500);
        }
    }

    public function getHotelById($id)
    {
        if (!empty($id)) {
            $stmt = $this->pdo->prepare("SELECT * FROM hotels WHERE id = ?");
            $stmt->execute([$id]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } else {
            http_response_code(500);
        }
    }

    public function getReservationByUserId($user_id)
    {
        if (!empty($user_id)) {
            $stmt = $this->pdo->prepare("SELECT reservations.id, rooms.room_number, hotels.name AS hotel_name, reservations.start_date, reservations.end_date
            FROM reservations
            JOIN rooms ON reservations.room_id = rooms.id
            JOIN hotels ON rooms.hotel_id = hotels.id
            WHERE reservations.user_id = ?");
            $stmt->execute([$user_id]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } else {
            http_response_code(500);
        }
    }


    public function getRoomByCategory($category)
    {
        if (!empty($category)) {
            $stmt = $this->pdo->prepare("SELECT rooms.id, hotels.name AS hotel_name, rooms.room_number, rooms.category, rooms.price
            FROM rooms
            INNER JOIN hotels ON rooms.hotel_id = hotels.id
            WHERE rooms.category = ?");
            $stmt->execute([$category]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } else {
            http_response_code(500);
        }
    }

    public function getAllHotels()
    {
        $stmt = $this->pdo->prepare("SELECT * FROM hotels");
        $stmt->execute();
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    public function getAllRooms()
    {
        $stmt = $this->pdo->prepare("SELECT rooms.id, hotels.name AS hotel_name, rooms.room_number, rooms.category, rooms.price
        FROM rooms
        INNER JOIN hotels
        ON rooms.hotel_id = hotels.id");

        $stmt->execute();
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    public function getHotelByAddr($address)
    {
        if (!empty($address)) {
            $stmt = $this->pdo->prepare("SELECT * FROM hotels WHERE address = ?");
            $stmt->execute([$address]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } else {
            http_response_code(500);
        }
    }

    public function getRoomByPrice($price)
    {
        if (!empty($price)) {
            $stmt = $this->pdo->prepare("SELECT rooms.id, hotels.name AS hotel_name, rooms.room_number, rooms.category, rooms.price
            FROM rooms
            INNER JOIN hotels ON rooms.hotel_id = hotels.id
            WHERE rooms.price < ?");
            $stmt->execute([$price]);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } else {
            http_response_code(500);
        }
    }

    public function insertReservation($room_id, $user_id, $start_date, $end_date)
    {
        $stmt = $this->pdo->prepare("INSERT INTO reservations (room_id, user_id, start_date, end_date) VALUES (?, ?, ?, ?)");
        return $stmt->execute([$room_id, $user_id, $start_date, $end_date]);
    }

    public function insertHotel($name, $address)
    {
        echo "INSERT INTO hotels (name, address) VALUES ($name, $address)";
        $stmt = $this->pdo->prepare("INSERT INTO hotels (name, address) VALUES (?, ?)");
        return $stmt->execute([$name, $address]);
    }

    public function insertRoom($hotel_id, $room_number, $category, $price)
    {
        $stmt = $this->pdo->prepare("INSERT INTO rooms (hotel_id, room_number, category, price) VALUES (?, ?, ?, ?)");
        return $stmt->execute([$hotel_id, $room_number, $category, $price]);
    }

    public function editReservation($id, $start_date, $end_date)
    {
        $stmt = $this->pdo->prepare("UPDATE reservations SET start_date = ?, end_date = ? WHERE id = ?");
        return $stmt->execute([$start_date, $end_date, $id]);
    }

    public function deleteReservation($id)
    {
        echo "DELETE FROM reservations WHERE id = $id";
        $stmt = $this->pdo->prepare("DELETE FROM reservations WHERE id = ?");
        return $stmt->execute([$id]);
    }


    public function selectUserByUsername($username)
    {
        $statement = $this->pdo->prepare("SELECT * FROM user U WHERE U.username = ?");
        $statement->execute([$username]);
        return $statement->fetchAll(PDO::FETCH_ASSOC);
    }

    public function selectIdByUsername($username)
    {
        $statement = $this->pdo->prepare("SELECT id
        FROM user U
        WHERE U.username = ?");
        $statement->execute([$username]);
        return $statement->fetchAll(PDO::FETCH_ASSOC);
    }

    public function show($value)
    {
        echo json_encode($value);
    }

    public function run()
    {
        if (isset($_GET['action']) && !empty($_GET['action'])) {
            switch ($_GET['action']) {

                case 'selectIdByUsername':
                    session_start();
                    $username = $_GET['username'];
                    $result = $this->selectIdByUsername($username);
                    $this->show($result);
                    break;

                case 'getHotelByName':
                    session_start();
                    $hotel = $_GET['hotel'];
                    $result = $this->getHotelByName($hotel);
                    $this->show($result);
                    break;

                case 'getReservationByUserId':
                    session_start();
                    $user_id = $_GET['user_id'];
                    $result = $this->getReservationByUserId($user_id);
                    $this->show($result);
                    break;

                case 'getRoomByCategory':
                    session_start();
                    $category = $_GET['category'];
                    $result = $this->getRoomByCategory($category);
                    $this->show($result);
                    break;

                case 'getAllHotels':
                    session_start();
                    $result = $this->getAllHotels();
                    $this->show($result);
                    break;

                case 'getHotelByAddr':
                    session_start();
                    $address = $_GET['address'];
                    $result = $this->getHotelByAddr($address);
                    $this->show($result);
                    break;

                case 'getRoomByPrice':
                    session_start();
                    $price = $_GET['price'];
                    $result = $this->getRoomByPrice($price);
                    $this->show($result);
                    break;

                case 'deleteReservation':
                    session_start();
                    $id = $_GET['id'];
                    $result = $this->deleteReservation($id);
                    $this->show($result);
                    break;

                case 'getAllRooms':
                    session_start();
                    $result = $this->getAllRooms();
                    $this->show($result);
                    break;

                case 'insertHotel':
                    session_start();
                    $name = $_GET['name'];
                    $address = $_GET['address'];
                    $result = $this->insertHotel($name, $address);
                    $this->show($result);
                    break;

                case 'insertRoom':
                    session_start();
                    $hotel_id = $_GET['hotel_id'];
                    $room_number = $_GET['room_number'];
                    $category = $_GET['category'];
                    $price = $_GET['price'];
                    $result = $this->insertRoom($hotel_id, $room_number, $category, $price);
                    $this->show($result);
                    break;

                case 'insertReservation':
                    session_start();
                    $room_id = $_GET['room_id'];
                    $user_id = $_GET['user_id'];
                    $start_date = $_GET['start_date'];
                    $end_date = $_GET['end_date'];
                    $result = $this->insertReservation($room_id, $user_id, $start_date, $end_date);
                    $this->show($result);
                    break;

                case 'editReservation':
                    session_start();
                    $start_date = $_GET['start_date'];
                    $end_date = $_GET['end_date'];
                    $id = $_GET['id'];
                    $result = $this->editReservation($id, $start_date, $end_date);
                    $this->show($result);
                    break;
            }
        }
    }
}
$conn = new DBConnection();
$conn->run();
