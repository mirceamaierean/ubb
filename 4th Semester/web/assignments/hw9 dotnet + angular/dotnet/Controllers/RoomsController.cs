using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Threading.Tasks;
using dotnet.Services;
using dotnet.Models;

namespace dotnet.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class RoomsController : ControllerBase
    {
        private readonly IService _roomService;

        public RoomsController(IService roomService)
        {
            _roomService = roomService;
        }

        [HttpGet]
        public async Task<ActionResult<List<Rooms>>> Get()
        {
            var rooms = await _roomService.GetRoomsAsync();
            return Ok(rooms);
        }

        [HttpGet("/api/Rooms/category/{category}")]
        public async Task<ActionResult<Rooms>> GetByCategory(string category)
        {
            var rooms = await _roomService.GetRoomsFilteredByCategoryAsync(category);

            if (rooms == null)
                return NotFound();

            return Ok(rooms);
        }
        
        [HttpGet("/api/Rooms/price/{price}")]
        public async Task<ActionResult<Rooms>> GetByPrice(int price)
        {
            var rooms = await _roomService.GetRoomsFilteredByPriceAsync(price);

            if (rooms == null)
                return NotFound();

            return Ok(rooms);
        }
    }
}