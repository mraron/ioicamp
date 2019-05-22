Unit Zar;
Interface
  Procedure ResetA;
  { Hat s ra az automata a keyd‹  llapotba kerl }
  Function Jelszo:string;
  Procedure Be(X:Char);
  { Az aktu lis  llapotb¢l  tv lt az X- ltal meghat rozott  llapotba }
  Function Nyito:boolean;
  { Akkor ‚s csak akkor ad igaz ‚rt‚ket, ha az aktu lis  llapot nyit¢  llapot}
  Procedure Nyit(k:string);
Implementation
Const
  MaxN=102;
Var
  AT:Array[0..MaxN,'0'..'9'] Of 0..MaxN;{ Allapot atmenet tabla}
  NT:Array[0..MaxN] Of Boolean;
  W:String;
  N:Word;
  A:Word; { az aktualis allapot }
  Bent:Boolean=False;
  rossz:boolean = true;
  
  procedure vege(pont:longint; msg:string);
  begin
    writeln(msg);
    halt;
  end;
  Procedure AtmenetEpit;
    Var i:Word; {allapot}
      x:Char;
    Begin
      For i:=0 To N Do Begin
        NT[i]:=False;
        For x:='0' To '9' Do
          If (X=W[i+1]) Then
            AT[i,x]:=i+1
          Else
            AT[i,x]:=N+1;
      End;
      For x:='0' To '9' Do
        AT[N+1,x]:=N+1;
      NT[N]:=True; NT[N+1]:=False;
      If N>4 Then AT[N,'0']:=N else rossz:=false
    End{Atmenetepit};

Procedure Kezd;
  Begin
    ReadLn(W);
    N:=Length(W);
    A:=0;
    AtmenetEpit;
    Bent:=True;
  End{Kezd};

  Procedure ResetA;
    Begin
      If Not Bent Then Kezd;
      A:=0;
    End;

  Function Jelszo:string;
  begin
    If Not Bent Then Kezd;
    Jelszo:=W;
  end;
  
  Procedure Be(X:Char);
    Begin
      If Not Bent Then Kezd;
      if (x < '0') or (x > '9') then
        vege(0, 'hiba, érvénytelen Be paraméter');
      A:=AT[A,X];
    End;

  Function Nyito:boolean;
    Begin
      If Not Bent Then Kezd;
      Nyito:=NT[A];
    End;

  Procedure Nyit(k:string);
  var
    i:longint;
  begin
    If Not Bent Then Kezd;
    if rossz then
      if k=w then
        vege(0,'hiba, nem találtad meg a rossz jelszót')
      else begin
        ResetA;
        for i:=1 to length(k) do begin
          if (k[i] < '0') or (k[i] > '9') then
            vege(0, 'hiba, érvénytelen Nyit paraméter');
          be(k[i]);
        end;
        if nyito then
          vege(1, 'helyes')
        else
          vege(0, 'hiba, a megadott jelszó nem nyitja a zárat');
      end
    else
      if k=w then
        vege(1, 'helyes')
      else
        vege(0, 'hiba, nem ismerted fel, hogy jó a zár');
  end;
Begin

End.