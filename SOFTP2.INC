{ Softporn Adventure, include file # 2 }



function locase( c : char ) : char;
(*===============================*)
begin
  case c of
    'A'..'Z':  c := chr( ord(c) + $20 );
    '':       c := '†';
    'Ž':       c := '„';
    '™':       c := '”';
  end;
  locase := c;
end;


procedure read_key ( var ch : char; cset : set_of_char );
(*=====================================================*)
var ch_up : char;
begin
  repeat
    read( kbd, ch );
    ch_up := upcase(ch);
    if ch_up in cset then
      writeln( ch )
    else
      write(#7);
  until ch_up in cset;
  ch := ch_up;
end;  { Read key }


procedure write_long_messg( messg_no : integer );
(*=============================================*)

const  EOL     = #$0D;
       NULL    = #0;

var    i, j       : integer;
       c          : char;

begin
  seek( messg_file, messg_no-1 );
  read( messg_file, messg_rec );
  for i:=1 to recsize-1 do
    begin
      c := messg_rec[i];
      if c=EOL then
        writeln
      else if c>=' ' then
        begin
          write(pred(c));
          if messg_no in [39,58,69] then
            delay(150);
        end;
    end; { for i=1 to recsize-1 do }
end;  { Write long messg }


procedure write_long_message( messg_no : integer );
(*===============================================*)
begin
  writeln;
  write_long_messg( messg_no );
end;  { Write long message }


procedure write_message( message : messg_string );
(*==============================================*)
begin
  writeln;
  writeln(message);
end;


procedure wait_for_space;
(*=====================*)
var c : char;
begin
  write('                    Press  <SPACE>  to continue  ');
  repeat
    read(kbd,c);
    if c<>' ' then write(#7);
  until c=' ';
end;


procedure cursor_to_bottom;
(*=======================*)
begin
  gotoXY(1,bottom_line);
end;


procedure cursor_next_to_bottom;
(*============================*)
begin
  gotoXY(1,bottom_line-1);
end;


procedure give_help;
(*================*)
var message : integer;
begin
  clrscr;
  writeln;
  writeln;
  for message:=70 to 72 do
    write_long_messg( message );
  writeln;
  wait_for_space;
  clrscr;
  cursor_to_bottom;
end;


procedure look_graffiti;
(*====================*)
var message : integer;
begin
  clrscr;
  for message:=59 to 62 do
    begin
      write_long_messg( message );
    end;
  wait_for_space;
  clrscr;
  cursor_to_bottom;
end;  { Look graffiti }


procedure purgatory;
(*================*)
var choice, door : integer;
    c : char;
begin
  delay(700);
  door := 0;
  repeat
    if door=0 then
      write_long_message( 65 )
    else
      begin
        writeln;
        writeln('You''re still here!');
        writeln;
      end;
    write('Choose your door: 1, 2 or 3??  ');
    read_key( c, ['1'..'3'] );
    choice := ord(c) - ord('0');
    door := ( random(3) + choice ) mod 3;
    game_position.game_ended := door=1;
  until door<>2;
end;  { Purgatory }


procedure bum_tells_story;
(*======================*)
var i,j : integer;
begin
  writeln;
  writeln('He looks at me and starts to speak:');
  delay(400);
  write_long_message( 39 );
  writeln;
  delay(300);
  for i:=0 to 128 do
    begin
      for j:=1 to i do
        write(' ');
      writeln('Like I did!!');
    end;
  for i:=1 to 5 do
    writeln;
  delay(500);
  writeln('He throws up and gives me back the bottle of wine.');
  writeln;
end;  { Bum tells story }


procedure watch_TV ( var TV_channel : integer );
(*============================================*)
var ch      : char;
begin
  repeat
    write('Which channel? (1-9) ');
    read_key( ch, ['1'..'9'] );
    TV_channel := ord(ch) - ord('0');
    write_long_message( 40 + TV_channel );
    writeln;
    write('Change the channel?  (y/n) ');
    read_key( ch, ['Y','N'] );
  until ch='N';
end;  { Watch TV }


procedure wine_in_taxi;
(*===================*)
begin
  write_long_message( 58 );
  delay(500);
  writeln;
  write('What shall I do? ');
  delay(1000);
  writeln;
  writeln;
  writeln('The idiot cab driver backs over me and kills me!!!!!!');
  purgatory;
end;  { Wine in taxi }


procedure stab_someone;
(*===================*)
begin
  writeln;
  writeln('OK - warmonger!');
  delay(1000);
  writeln('Parry!!');
  delay(500);
  writeln('Thrust!!!');
  delay(1000);
  writeln('I just got myself!!');
  purgatory;
end;  { Stab }


procedure falling_down;
(*===================*)
var i : integer;
begin
  for i:=1 to 50 do
    writeln('Aaaaaeeeeeiiiiiiii!!!!!!!!');
  delay(300);
  writeln('Splaaatttttt!!!!!');
  if game_position.verb<>jump then
    begin
      delay(500);
      writeln;
      writeln('I should have used safety rope!!!!!!!!');
    end;
  purgatory;
end;  { Falling down }


procedure play_slot( var money : integer );
(*=======================================*)
const slot : array[0..4] of char = ( '!', '#', '*', '$', '^' );
      slot_figs = 5;
var answer : char;
    i, x1, x2, x3 : integer;
begin
  writeln;
  writeln('This will cost $100 each time');
  repeat
    randomize;
    write('You have $',money,'00.  Would you like to play?  (y/n)  ');
    read_key( answer, ['Y','N'] );
    if answer='Y' then
      begin
        for i:=1 to 30 do
          begin
            x1 := random(slot_figs);
            x2 := random(slot_figs);
            x3 := random(slot_figs);
            delay(30);
            write( #13, slot[x1]:1, slot[x2]:5, slot[x3]:5 );
          end;
        writeln;
        if (x1=x2) and (x2=x3) then
          begin
            writeln('Triples!!!!!! You win $1500');
            money := money + 15;
          end
        else if (x1=x2) or (x2=x3) or (x3=x1) then
          begin
            writeln('A pair!  You win $300');
            money := money + 3;
          end
        else
          begin
            writeln('You lose!');
            money := money - 1;
          end;
      end;
  until (money<1) or (answer='N');
  writeln;
  if money<1 then
    begin
      writeln('I''m broke!!! -- that means death!!!!!!!');
      purgatory;
    end;
end;  { Play slot }


procedure play_21( var money : integer );
(*=====================================*)
const card_name : array[1..13] of string[7]
   = ( 'an Ace', 'a 2', 'a 3', 'a 4', 'a 5', 'a 6', 'a 7',
       'an 8', 'a 9', 'a 10', 'a Jack', 'a Queen', 'a King' );
      delay_21 = 400;
var answer : char;
    dollars, code, mi, md, yd, ym, ad, am, a, y, z, ac, i : integer;
    answer_ok, game_over : boolean;
    dollar_string, doll_00 : string[20];
    card : string[7];

procedure deal_card;
(*----------------*)
begin
  z := random(13) + 1;
  y := 0;
  ac := 0;
  card := card_name[z];
  if z>10 then z := 10;
  if z=1  then z := 11;
  if z>9  then y := 1;
  if z=11 then ac := 1;
end;

procedure check;
(*------------*)
begin
  if (md>21) and (ad>0) then
    begin
      ad := ad - 1;
      md := md - 10;
    end;
    delay(delay_21);
    writeln('The dealer has ',md);
    if md<17 then
      a := 6
    else if (md>21) or (mi>md) then
      begin
        delay(delay_21);
        writeln('You win!!');
        money := money + dollars;
        game_over := true;
      end
    else if mi<md then
      begin
        delay(delay_21);
        writeln('You lose!');
        money := money - dollars;
        game_over := true;
      end
    else {if mi=md then}
      begin
        delay(delay_21);
        writeln('Tie!');
        game_over := true;
      end;
end;

procedure check_hit;
(*----------------*)
begin
  if (mi>21) and (am>0) then
    begin
      am := am - 1;
      mi := mi - 10;
    end;
  delay(delay_21);
  writeln('Your total is ',mi,'.');
  if mi>21 then
    begin
      delay(delay_21);
      writeln('Busted!');
      money := money - dollars;
      game_over := true;
    end
  else if (ym=2) and (mi=21) then
    begin
      delay(delay_21);
      writeln('You''ve got a ***BLACKJACK***');
      money := money + dollars + dollars;
      game_over := true;
    end
  else if (yd=2) and (md=21) then
    begin
      delay(delay_21);
      writeln('The dealer has a ***BLACKJACK***');
      money := money - dollars;
      game_over := true;
    end
  else
    begin
      delay(delay_21);
      write('Would you like a hit?  (y/n)  ');
      read_key( answer, ['Y','N']);
      if answer='N' then check;
    end;
end;

begin
  writeln;
  repeat
    randomize;
    mi := 0;
    md := 0;
    yd := 0;
    ym := 0;
    ad := 0;
    am := 0;
    repeat
      answer_ok := false;
      write('You have $',money,'00.  How many dollars would you like to bet? ');
      readln(dollar_string);
      repeat
        i := pos( ' ', dollar_string);
        if i>0 then delete( dollar_string, i, 1 );
      until i=0;
      i := length(dollar_string);
      if i>2 then
        begin
          doll_00 := copy( dollar_string, i-1, 2 );
          delete( dollar_string, i-1, 2 );
        end
      else
        begin
          doll_00 := dollar_string;
          dollar_string := '';
        end;
      val( doll_00, dollars, code );
      if code=0 then val( dollar_string, dollars, code );
      if (code<>0) or (dollars<=0) then
        writeln('Huh?')
      else if doll_00 <> '00' then
        writeln('$100 increments only!!')
      else if dollars > money then
        writeln('You don''t have that much!!!')
      else
        answer_ok := true;
    until answer_ok;

    a := 1;
    game_over := false;
    repeat
      deal_card;
      delay(delay_21);
      case a of
        1,3 : begin
                mi := mi + z;
                writeln('You''re dealt ',card);
                ym := ym + y;
                am := am + ac;
                a := a + 1;
              end;
        2   : begin
                md := md + z;
                writeln('The dealer gets a card down');
                yd := yd + y;
                ad := ad + ac;
                a := a + 1;
              end;
        4   : begin
                md := md + z;
                writeln('The dealer gets ',card);
                a := 5;
                ad := ad + ac;
                yd := yd + y;
                check_hit;
              end;
        5   : begin
                mi := mi + z;
                writeln('You get ',card);
                am := am + ac;
                check_hit;
              end;
        6   : begin
                md := md + z;
                writeln('The dealer gets ',card);
                ad := ad + ac;
                check;
              end;
      end;
    until game_over;
    if money<1 then
      begin
        writeln('You''re out of money!!!  So long!!!!!!!!!!');
        purgatory;
      end
    else
      begin
        write('Play again?? (y/n)  ');
        read_key( answer, ['Y','N'] );
      end;
  until (answer='N') or (money<1);
end;  { Play 21 }


procedure buy_rubber;
(*=================*)
var answer : char;
    i      : integer;
begin
  with game_position do
    begin
      rubber_lubricated := 'non-lubricated';
      rubber_ribbed := 'non-ribbed';
      writeln;
      writeln('The man leans over the counter and whispers:');
      write('What color? ');  readln(rubber_color);
      for i:=1 to length(rubber_color) do
        rubber_color[i] := locase(rubber_color[i]);
      write('And for a flavor? ');  readln(rubber_flavor);
      for i:=1 to length(rubber_flavor) do
        rubber_flavor[i] := locase(rubber_flavor[i]);
      write('Lubricated or not? (y/n) ');
      read_key( answer, ['Y','N'] );
      if answer='Y' then delete( rubber_lubricated, 1, 4 );
      write('Ribbed? (y/n) ');
      read_key( answer, ['Y','N'] );
      if answer='Y' then delete( rubber_ribbed, 1, 4 );
      writeln('He yells -- This pervert just bought a ',rubber_color,', ');
      writeln(rubber_flavor,'-flavored, ',rubber_lubricated,', ',
              rubber_ribbed,' rubber!!!!');
      writeln('A lady walks by and looks at me in disgust!!!!');
      writeln;
    end;
end;  { Buy rubber }


procedure OK;
(*=========*)
begin
  write_message('OK');
end;


procedure _open( var object_open : boolean );
(*=========================================*)
begin
  if object_open then
    write_message('It''s already open!!')
  else
    begin
      OK;
      object_open := true;
    end;
end;


procedure _close( var object_open : boolean );
(*=========================================*)
begin
  if not object_open then
    write_message('It''s already closed!!')
  else
    begin
      OK;
      object_open := false;
    end;
end;
