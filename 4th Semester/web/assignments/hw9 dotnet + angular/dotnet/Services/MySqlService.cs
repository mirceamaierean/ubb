using MySql.Data.MySqlClient;
using dotnet.Models;

namespace dotnet.Services
{
    public class MySqlService : IService
    {
        private readonly string _connectionString;

        public MySqlService(IConfiguration configuration)
        {
            _connectionString = configuration.GetConnectionString("DefaultConnection");
        }

        public async Task<List<Hotels>> GetHotelsAsync()
        {
            var hotels = new List<Hotels>();

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                await connection.OpenAsync();

                string query = "SELECT id, name, address from hotels";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                using (MySqlDataReader reader = (MySqlDataReader)await command.ExecuteReaderAsync())
                {
                    while (await reader.ReadAsync())
                    {
                        hotels.Add(new Hotels
                        {
                            Id = reader.GetInt32("id"),
                            Name = reader.GetString("name"),
                            Address = reader.GetString("address"),
                        });
                    }
                }
            }

            return hotels;
        }

        public async Task<List<Hotels>> GetHotelsFilteredByNamesAsync(string name)
        {
            var hotels = new List<Hotels>();

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                connection.Open();

                string query = "SELECT id, name, address FROM hotels WHERE name LIKE @name";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@name", $"%{name}%");

                    using (MySqlDataReader reader = (MySqlDataReader)command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            hotels.Add(new Hotels
                            {
                                Id = reader.GetInt32("id"),
                                Name = reader.GetString("name"),
                                Address = reader.GetString("address")
                            });
                        }
                    }
                }
            }
            return hotels;
        }
        
        public async Task<List<Hotels>> GetHotelsFilteredByAddressAsync(string address)
        {
            var hotels = new List<Hotels>();

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                connection.Open();

                string query = "SELECT id, name, address FROM hotels WHERE address LIKE @address";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@address", $"%{address}%");

                    using (MySqlDataReader reader = (MySqlDataReader)command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            hotels.Add(new Hotels
                            {
                                Id = reader.GetInt32("id"),
                                Name = reader.GetString("name"),
                                Address = reader.GetString("address")
                            });
                        }
                    }
                }
            }
            return hotels;
        }

        public async Task<Users> Authenticate(string username, string password)
        {
            Users user = null;

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                await connection.OpenAsync();

                string query = "SELECT id, username, password FROM user WHERE username = @username AND password = @password";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@username", username);
                    command.Parameters.AddWithValue("@password", password);

                    using (MySqlDataReader reader = (MySqlDataReader)await command.ExecuteReaderAsync())
                    {
                        if (await reader.ReadAsync())
                        {
                            user = new Users
                            {
                                Id = reader.GetInt32("id"),
                                Username = reader.GetString("username"),
                                Password = reader.GetString("password")
                            };
                        }
                    }
                }
            }

            return user;
        }
        
         public async Task<List<Rooms>> GetRoomsAsync()
        {
            var rooms = new List<Rooms>();

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                await connection.OpenAsync();

                string query = @"
            SELECT rooms.id, hotels.name AS hotel_name, rooms.room_number, rooms.category, rooms.price
            FROM rooms
            INNER JOIN hotels
            ON rooms.hotel_id = hotels.id";
                

                using (MySqlCommand command = new MySqlCommand(query, connection))
                using (MySqlDataReader reader = (MySqlDataReader)await command.ExecuteReaderAsync())
                {
                    while (await reader.ReadAsync())
                    {
                        rooms.Add(new Rooms
                        {
                            Id = reader.GetInt32("id"),
                            HotelName = reader.GetString("hotel_name"),
                            RoomNumber = reader.GetInt32("room_number"),
                            Category = reader.GetString("category"),
                            Price = reader.GetInt32("price")
                        });
                    }
                }
            }

            return rooms;
        }

        public async Task<List<Rooms>> GetRoomsFilteredByCategoryAsync(string category)
        {
            var rooms = new List<Rooms>();

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                connection.Open();

                string query = @"
            SELECT rooms.id, hotels.name AS hotel_name, rooms.room_number, rooms.category, rooms.price
            FROM rooms
            INNER JOIN hotels
            ON rooms.hotel_id = hotels.id
            WHERE rooms.category like @category";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@category", category);

                    using (MySqlDataReader reader = (MySqlDataReader)command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            rooms.Add(new Rooms
                            {
                                Id = reader.GetInt32("id"),
                                HotelName = reader.GetString("hotel_name"),
                                RoomNumber = reader.GetInt32("room_number"),
                                Category = reader.GetString("category"),
                                Price = reader.GetInt32("price")
                            });
                        }
                    }
                }
            }

            return rooms;
        }
       
        public async Task<List<Rooms>> GetRoomsFilteredByPriceAsync(int price)
        {
            var rooms = new List<Rooms>();

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                connection.Open();

                string query = @"
            SELECT rooms.id, hotels.name AS hotel_name, rooms.room_number, rooms.category, rooms.price
            FROM rooms
            INNER JOIN hotels
            ON rooms.hotel_id = hotels.id
            WHERE rooms.price <= @price";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@price", price);

                    using (MySqlDataReader reader = (MySqlDataReader)command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            rooms.Add(new Rooms
                            {
                                Id = reader.GetInt32("id"),
                                HotelName = reader.GetString("hotel_name"),
                                RoomNumber = reader.GetInt32("room_number"),
                                Category = reader.GetString("category"),
                                Price = reader.GetInt32("price")
                            });
                        }
                    }
                }
            }

            return rooms;
        }
        
        public async Task<List<Bookings>> GetBookingsAsync()
        {
            var bookings = new List<Bookings>();

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                await connection.OpenAsync();

                string query = "SELECT id, room_id, user_id, start_date, end_date FROM bookings";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                using (MySqlDataReader reader = (MySqlDataReader)await command.ExecuteReaderAsync())
                {
                    while (await reader.ReadAsync())
                    {
                        bookings.Add(new Bookings
                        {
                            Id = reader.GetInt32("id"),
                            RoomId = reader.GetInt32("room_id"),
                            UserId = reader.GetInt32("user_id"),
                            StartDate = reader.GetDateTime("start_date"),
                            EndDate = reader.GetDateTime("end_date")
                        });
                    }
                }
            }

            return bookings;
        }

        public async Task<Bookings> GetBookingByIdAsync(int id)
        {
            Bookings booking = null;

            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                await connection.OpenAsync();

                string query = "SELECT id, room_id, user_id, start_date, end_date FROM bookings WHERE id = @id";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@id", id);

                    using (MySqlDataReader reader = (MySqlDataReader)await command.ExecuteReaderAsync())
                    {
                        if (await reader.ReadAsync())
                        {
                            booking = new Bookings
                            {
                                Id = reader.GetInt32("id"),
                                RoomId = reader.GetInt32("room_id"),
                                UserId = reader.GetInt32("user_id"),
                                StartDate = reader.GetDateTime("start_date"),
                                EndDate = reader.GetDateTime("end_date")
                            };
                        }
                    }
                }
            }

            return booking;
        }

        public async Task<Bookings> CreateBookingAsync(Bookings booking)
        {
            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                await connection.OpenAsync();

                string query = "INSERT INTO bookings (room_id, user_id, start_date, end_date) VALUES (@room_id, @user_id, @start_date, @end_date); SELECT LAST_INSERT_ID();";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@room_id", booking.RoomId);
                    command.Parameters.AddWithValue("@user_id", booking.UserId);
                    command.Parameters.AddWithValue("@start_date", booking.StartDate);
                    command.Parameters.AddWithValue("@end_date", booking.EndDate);

                    booking.Id = Convert.ToInt32(await command.ExecuteScalarAsync());
                }
            }

            return booking;
        }

        public async Task<bool> DeleteBookingAsync(int id)
        {
            using (MySqlConnection connection = new MySqlConnection(_connectionString))
            {
                await connection.OpenAsync();

                string query = "DELETE FROM bookings WHERE id = @id";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@id", id);

                    int affectedRows = await command.ExecuteNonQueryAsync();
                    return affectedRows > 0;
                }
            }
        }
    }
}