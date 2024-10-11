using dotnet.Models;

namespace dotnet.Services
{
    public interface IService
    {
        Task<List<Hotels>> GetHotelsAsync();
        Task<List<Hotels>> GetHotelsFilteredByNamesAsync(string name);
        
        Task<List<Hotels>> GetHotelsFilteredByAddressAsync(string address);
        // insert hotels
        // void InsertHotels(Hotels hotel);

        Task<Users> Authenticate(string username, string password);

        Task<List<Rooms>> GetRoomsAsync();
        
        Task<List <Rooms>> GetRoomsFilteredByCategoryAsync(string category);
        
        Task<List<Rooms>> GetRoomsFilteredByPriceAsync(int price);

        Task<List<Bookings>> GetBookingsAsync();
        Task<Bookings> GetBookingByIdAsync(int id);
        Task<Bookings> CreateBookingAsync(Bookings booking);
        Task<bool> DeleteBookingAsync(int id);
    }
}