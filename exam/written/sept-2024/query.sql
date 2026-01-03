select g.GroupId, g.GroupName, sum(fp.PaymentAmount) as TotalAmount
from Groups g
join Children c on c.GroupId = g.GroupId
join FeePayments fp on c.ChildId = fp.ChildId
group by g.GroupId, g.GroupName