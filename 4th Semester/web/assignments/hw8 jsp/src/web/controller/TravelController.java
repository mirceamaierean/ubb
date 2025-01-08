package web.controller;

import web.domain.*;
import web.model.*;

import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.List;

public class TravelController extends HttpServlet {
    DBManager dbManager = new DBManager();

    @Override
    public void init() throws ServletException {
        dbManager.connect();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        try {
            String cityId = req.getParameter("cityId");
            if (cityId != null) {
                Travel travel = new Travel(user.getId(), LocalDateTime.now());
                dbManager.addTravel(travel);
                resp.sendRedirect("travels");
                return;
            }

            List<Travel> travels = dbManager.getTravelsByUser(user.getId());
            req.setAttribute("travels", travels);
            req.getRequestDispatcher("/travels.jsp").forward(req, resp);
        } catch (SQLException e) {
            throw new ServletException(e);
        }
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
            resp.sendRedirect("travels");
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
}
