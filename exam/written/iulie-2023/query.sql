SELECT COUNT(*) as TotalNumberOfArticles
FROM Articles a
    INNER JOIN Categories c ON c.CategoryId = a.CategoryId
    INNER JOIN Journalists j ON j.JournalistId = a.JournalistId
    INNER JOIN Newspapers n ON n.NewspaperId = j.NewspaperId
WHERE c.Name = 'Economics' AND n.NewspaperName = 'Universe'