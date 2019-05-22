unit tudakozo;
//gyakorló könyvtári modul
interface
  function hany:integer;
  function kerdes(x, y:integer):integer;
  procedure megoldas(m:integer);

implementation
  const
    Init:boolean=true;
var
    N,C,K:integer;
    kerd:integer;
function hany:integer;
begin
	readln(N,C,K);
    kerd:=0;
    Init:=false;
    hany:=N;
end{hany};

function kerdes(x,y:integer):integer;
begin
	if(Init) then begin
		writeln('HIBA: Előbb a hany műveletet kell hívni!');
		halt;
	end;
	inc(kerd);
	if (kerd>3*N )then begin
		writeln('HIBA: túl sok kérdés volt már!');
		halt;
	end;
	if(x<1)or(x>N)or(y<1)or(y>N)then begin
		writeln('HIBA: hibás sorszám!',x,'::',y);
		halt;
	end;
	if (x=K)and(y<>C)or(y=K)and(x<>C) then
		kerdes:=0
	else
		kerdes:=1;
end{kerdes};
procedure megoldas(m:integer);
begin
{Itt ellenőrzik, hogy a feltett kérdések alapján m lehet-e megoldás!}
	if (m<1) or(m>N)then begin
		writeln('HIBA: hibás sorszám');
		halt;
	end;
	if (m=C) then begin
		if kerd<=2*N then
			writeln('HELYES, centrum=',m,' kérdesszám = ',kerd,' <=2*N')
		else
			writeln('HELYES, centrum=',m,' kérdesszám = ',kerd,' <=3*N');
	end else 
		writeln('HIBÁS');
	halt;
end{megoldas};

begin

end.
