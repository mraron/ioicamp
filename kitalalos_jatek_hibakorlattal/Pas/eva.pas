unit eva;
interface
  function GetN:longint;
  function GetH:integer;
  function Kerdes(A,B:longint):integer;
  procedure Megoldas(x:longint);
implementation
  const
    MaxH=14;
    maxM=4000000;
    Init:boolean=true;
  var
    N,H:longint;
    bal,jobb:longint;
    Kerd:longint;
	
  procedure Vege(ki:longint; msg:String);
  begin{Vege}
	writeln(msg);
    Halt;
  end{Vege};

procedure Elofel;
begin{Elofel}
  readln(N, H);
  bal:=1; jobb:=N;
  kerd:=0;
  init:=false;
end{Elofel};

  function GetN:longint;
  begin
    if Init then begin
      EloFel;
      Init:=false;
    end;
    GetN:=N;
  end{GetN};
  
  function GetH:integer;
  begin
    if Init then begin
       EloFel;
      Init:=false;
    end;
    GetH:=H;
  end{GetH};

  function Kerdes(A,B:longint):integer;
  var v:integer ;
  begin{Kerdes}
    if Init then begin
      Vege(0,'hiba, először GetN-t kell hívni');
    end;
    if (A<1)or(A>N)or(B<1)or(B>N)or(A>B) then begin
      Vege(-1,'hiba, érvénytelen paraméter Kerdes-ben');
    end;
	if A<bal then A:=bal;
    if B>jobb then B:=jobb;
    v:=0;
    bal:=A; jobb:=B;
    inc(kerd);
    Kerdes:=v;
  end{Kerdes};

  procedure Megoldas(x:longint);
  begin{Megoldas}
    if Init then begin
      vege(0, 'hiba, először GetN-t kell hívni');
    end;
    if (bal<>jobb) then 
		vege(0, 'hiba, blöfföltél');
	if (x<>bal) then
       Vege(0,'hiba, rossz válasz');
    vege(1, 'helyes');
  end{Megoldas};
begin

end.
