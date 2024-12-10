int a;read(a);int i;i=1;int sum;sum=0;while(i<=a){if(a%i==0){sum=sum+i;}i=i+1;}write(sum);

\documentclass{article}
\usepackage{algorithm}
\usepackage{algorithmic}
\usepackage{amsmath}

\begin{document}

\section*{Problema spectacolelor}


\paragraph{Date de intrare}
Pe prima linie a fișierului de intrare \texttt{spectacole.in} se află numărul $n$, numărul de spectacole propus. Pe următoarele $n$ linii se vor afla 4 valori, primele două reprezentând ora și minutul începerii spectacolului curent, iar ultimele două reprezentând ora și minutul terminării spectacolului.

\paragraph{Date de ieșire}
Fișierul de ieșire \texttt{spectacole.out} conține o singură linie, pe aceasta vor fi scrise numerele de ordine ale spectacolelor care îndeplinesc soluția problemei, separate printr-un spațiu.

\paragraph{Restricții}
$n \leq 100$

\paragraph{Exemplu}

\begin{itemize}
    \item \textbf{Fișier de intrare:} \texttt{spectacole.in}
    \begin{verbatim}
    5
    12 30 16 30
    15 0 18 0
    10 0 18 30
    18 0 20 45
    12 15 13 0
    \end{verbatim}
    
    \item \textbf{Fișier de ieșire:} \texttt{spectacole.out}
    \begin{verbatim}
    5 2 4
    \end{verbatim}
\end{itemize}

\begin{algorithm}
\caption{Algoritmul de selecție a spectacolelor}
\begin{algorithmic}[1]

\State \textbf{Input:} Fișierul \texttt{spectacole.in} conține $n$ (numărul de spectacole) și pentru fiecare spectacol $S_i$ timpul de început și sfârșit în formatul (ora, minut).
\State \textbf{Output:} Fișierul \texttt{spectacole.out} conține numerele de ordine ale spectacolelor selectate, separate prin spațiu, astfel încât să maximizeze numărul de spectacole care pot fi vizionate.

\Procedure{Citeste}{}
    \State Deschide fișierul \texttt{spectacole.in}
    \State Citește $n$, numărul de spectacole
    \For{$i = 1$ to $n$}
        \State Citește ora și minutul de început și transformă în minute totale $\rightarrow inceput[i]$
        \State Citește ora și minutul de sfârșit și transformă în minute totale $\rightarrow sfarsit[i]$
        \State Salvează numărul de ordine $i$ în vectorul $nr[i]$
    \EndFor
    \State Închide fișierul \texttt{spectacole.in}
\EndProcedure

\Procedure{Sorteaza}{}
    \State \textbf{Comentariu:} Sortare BubbleSort pe baza timpului de sfârșit al fiecărui spectacol
    \Repeat
