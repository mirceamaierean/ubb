package web.controller;

import com.google.gson.Gson;
import web.model.DBManager;
import web.domain.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/cities")
public class CityController extends HttpServlet {
    private DBManager dbManager;

    @Override
    public void init() {
        dbManager = new DBManager();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        String cityId = req.getParameter("cityId");
        String ajax = req.getHeader("X-Requested-With");

        try {
            if (cityId == null) {
                List<City> cities = dbManager.getAllCities();
                req.setAttribute("cities", cities);
                req.setAttribute("neighbors", new ArrayList<>()); // Ensure neighbors is always set

                req.getRequestDispatcher("/cities.jsp").forward(req, resp);
            } else {
                int cityIdInt = Integer.parseInt(cityId);
                List<City> neighbors = dbManager.getNeighbors(cityIdInt);

                for (City neighbor : neighbors) {
                    System.out.println(neighbor);
                }

                if ("XMLHttpRequest".equals(ajax)) {
                    // Return JSON response for AJAX request
                    resp.setContentType("application/json");
                    resp.setCharacterEncoding("UTF-8");
                    String json = new Gson().toJson(neighbors);
                    resp.getWriter().write(json);
                } else {
                    // Regular request, forward to JSP
                    req.setAttribute("neighbors", neighbors);
                    req.getRequestDispatcher("/cities.jsp").forward(req, resp);
                }
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        // get latest travel from session

        Travel travel = (Travel) session.getAttribute("currentTravel");
        System.out.println("travel: " + travel);

        // get selected cities from request body
        String selectedCities = req.getParameter("selectedCities");
        // split the string into an array of city IDs, the separator is _
        List<String> cityIds = List.of(selectedCities.split("_"));


        if (travel != null && cityIds != null) {
            try {
                // Insert all pins for the travel
                dbManager.addPins(travel.getId(), cityIds);

                // End the travel
                travel.setFinished(true);
                dbManager.endTravel(travel.getId());  // Ensure the travel is marked as ended

                // Clear session attributes
                session.removeAttribute("selectedCities");
                session.removeAttribute("currentTravel");
                session.removeAttribute("stepNumber");

            } catch (SQLException e) {
                throw new ServletException(e);
            }
        }
    }

    @Override
    public void destroy() {
        dbManager.close();
    }
}
