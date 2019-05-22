unit valasz;

interface
  Function induloszam: integer;
  Function kerdes(i,j: integer): integer;
  Procedure megoldas(i: integer);
  
implementation      
  const 
		Init:boolean=false;
		maxn=1024;
  var 
		n,db: integer;
    r: array[1..maxn] of integer;
//
procedure Vege(pont:integer; Uzi:string);
    begin
      writeln(pont);
      writeln(Uzi);
      halt;
    end;
    
  Function induloszam: integer;
    var i: integer;
  begin
    Init:=true;
    readln(n); db:=0;
    for i:=1 to n do read(r[i]);
    readln;
    induloszam:=n;
  end;
   
  Function kerdes(i,j: integer): integer;
  begin
  if not Init then Vege(0,'Protokoll hiba');
    inc(db);
    if (j>=0) and (j<=31) and (i>=1) and (i<=n) then kerdes:=(r[i] shr j) mod 2
    else Vege(0,'Protokoll hiba');
  end;
   
  Procedure megoldas(i: integer);
  begin
		if not Init then Vege(0,'Protokoll hiba');
    if i=r[n] then begin
			if db<=2*n-2 then begin
				Vege(3,'Helyes, kérdésszám <= 2*N-2');
			end else if db<=3*n-4 then begin
				Vege(2,'Helyes, kérdésszám <= 3*N-4');
			end else if db<=10*n then begin
				Vege(1,'Helyes, kérdésszám <= 10*N');
			end else begin
				Vege(0,'Helyes válasz, de a kérdésszám > 10*N');
			end;
    end else begin
			Vege(0,'Hibás válasz');
		end;
  end;
   
begin
end.
