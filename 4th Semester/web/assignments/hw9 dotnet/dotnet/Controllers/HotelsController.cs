using Microsoft.AspNetCore.Mvc;
using dotnet.Services;
using dotnet.Models;

namespace dotnet.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class HotelsController : ControllerBase
    {
        private readonly IService _myService;

        public HotelsController(IService myService)
        {
            _myService = myService;
        }

        [HttpGet]
        public async Task<ActionResult<List<Hotels>>> Get()
        {
            var hotels = await _myService.GetHotelsAsync();
            return Ok(hotels);
        }
        
        [HttpGet("{name}")]
        public async Task<ActionResult<Users>> GetByName(string name)
        {
            var hotels = await _myService.GetHotelsFilteredByNamesAsync(name);

            if (hotels == null)
                return NotFound();

            return Ok(hotels);
        }

        [HttpGet("/api/Hotels/address/{address}")]
        public async Task<ActionResult<Users>> GetByAddress(string address)
        {
            var hotels = await _myService.GetHotelsFilteredByAddressAsync(address);

            if (hotels == null)
                return NotFound();

            return Ok(hotels);
        }
    }
}