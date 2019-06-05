Unit Game;
Interface

Procedure MyMove(i:Integer);
Function  YourMove:Integer;
Function  Pit(i:Integer):Integer;

Implementation
Const
  Init:boolean=true;
  NemJo=0;
  Jo=1;
  Szurke=2;
  Feher=3;
  kor:array[1..4,0..2] of 1..4=((2,3,4),(3,4,1),(4,1,2),(1,2,3));
Type
  Allas=array[1..4] of byte;
Var
  LastMove:Integer;
  A:Allas;

procedure Lep(const a:Allas; i:Byte; var aa:Allas);
Var j:integer;
  kavics:byte;
begin
  for j:=1 to 4 do aa[j]:=a[j];
  aa[i]:=0;
  kavics:= a[i]-1;
  if kavics=0 then exit;
  j:=0;
  repeat
    inc(aa[kor[i,j]]);
    dec(kavics);
    j:=(j+1) mod 3;
  until kavics=0;

end{Lep};

Procedure EndGame(pont: longint; msg: string);
Begin
  writeln(msg);
  Halt;
End;

Procedure Start;
Var
  i:Longint;
  z,x:longint;
Begin
  z:=0;
  for i:=1 to 4 do begin
    read(x);
    A[i]:=x;
    z:=z+x;
  end;

  Init:=false;
End{Start};

Function YourMove:Integer;
Begin{YourMove}
  If Init Then Start;
  YourMove:=LastMove;
End{YourMove};

Procedure MyMove(i:Integer);
Var
  AA,A3,A4:Allas;
  L3:Boolean;
Begin
  If Init Then Start;
  If (i<1)or(i>2)  Then Begin
    EndGame(0, 'hiba, érvénytelen paraméter MyMove-ban');   {illegal move}
  End;
  If A[i]=0 Then Begin
    EndGame(0, 'hiba, érvénytelen paraméter MyMove-ban');   {illegal move}
  End;

  Lep(A,i,Aa);
  A:=Aa;
  if A[3]+A[4]=0 then  EndGame(1, 'helyes');
  L3:=false;
  if A[3]>0 then begin
    Lep(A,3,A3);
    L3:=true;
  end else begin
    Lep(A,4,A4);
  end;
  if L3 then begin
      A:=A3;
      Lastmove:=3;
      if A[1]+A[2]=0 then EndGame(0, 'hiba, vesztettél');
      exit;
  end else begin
      A:=A4;
      Lastmove:=4;
      if A[1]+A[2]=0 then EndGame(0, 'hiba, vesztettél');
      exit;
  end;

End{MyMove};

Function  Pit(i:Integer):Integer;
Begin
  If Init Then Start;
  If (i<1) Or (i>4) Then Begin
    EndGame(0, 'hiba, érvénytelen paraméter Pit-ben');
  End;
  Pit:=A[i];
End{Pit};

End.
