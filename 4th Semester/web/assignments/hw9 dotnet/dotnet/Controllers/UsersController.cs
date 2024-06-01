using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;
using dotnet.Services;
using dotnet.Models;

namespace dotnet.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class UserController : ControllerBase
    {
        private readonly IService _service;

        public UserController(IService service)
        {
            _service = service;
        }

        [HttpPost("login")]
        public async Task<ActionResult<Users>> Login([FromBody] Users login)
        {
            var user = await _service.Authenticate(login.Username, login.Password);

            if (user == null)
                return Unauthorized(new { message = "Username or password is incorrect" });

            return Ok(user);
        }

        [HttpPost("logout")]
        public IActionResult Logout()
        {
            return Ok(new { message = "Logged out successfully" });
        }
    }
}