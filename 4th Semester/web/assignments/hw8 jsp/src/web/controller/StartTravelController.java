package web.controller;

import web.model.DBManager;
import web.domain.Travel;
import web.domain.User;
import web.domain.City;

import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.List;

public class StartTravelController extends HttpServlet {
    private DBManager dbManager;

    @Override
    public void init() throws ServletException {
        dbManager = new DBManager();
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        try {
            Travel travel = new Travel(user.getId(), LocalDateTime.now());
            dbManager.addTravel(travel);
            session.setAttribute("currentTravel", travel);

            List<City> cities = dbManager.getAllCities();
            req.setAttribute("cities", cities);
            req.getRequestDispatcher("/cities.jsp").forward(req, resp);
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
}
