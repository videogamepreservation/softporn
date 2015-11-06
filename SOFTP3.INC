{ Softporn Adventure, include file # 3 }



procedure newlines( lines : integer );
(*==================================*)
var i : integer;
begin
  for i:=1 to lines do writeln;
end;


procedure I_cant_go_that_way;
(*=========================*)
begin
  write_message( 'I can''t go that way!' );
end;


procedure cant_do_that;
(*===================*)
var messg : integer;
begin
  messg := random(8) + 1;
  case messg of
    1: writeln('Huh?');
    2: writeln('Ummm......huh?');
    3: writeln('You''re nuts!');
    4: writeln('You can''t be serious!!');
    5: writeln('Not bloody likely!!');
    6: writeln('I don''t know how to.');
    7: writeln('An interesting idea....');
    8: writeln('I can''t do that.');
  end;
end;


procedure huh;
(*==========*)
begin
  write_message('Huh?');
end;


procedure I_cant_do_that;
(*=====================*)
begin
  writeln;
  cant_do_that;
end;


procedure I_dont_know_that_word;
(*============================*)
begin
  write_message( 'I don''t know that word!' );
end;


procedure find_me_one;
(*==================*)
var messg : integer;
begin
  messg := random(4) + 1;
  writeln;
  case messg of
    1: writeln('Find me one!!');
    2: writeln('I don''t see it here!');
    3: writeln('I can''t find it here!');
    4: writeln('You have to find it first!');
  end;
end;


procedure I_dont_have_it;
(*=====================*)
begin
  write_message('I don''t have it!!');
end;


procedure I_already_have_it;
(*========================*)
begin
  with game_position do
    write_message( 'I already have it!!');
end;


procedure I_see_nothing_special;
(*============================*)
begin
  write_message('I see nothing special');
end;


procedure I_see_something( object : objects; messg : str25 );
(*=========================================================*)
begin
  with game_position do
    begin
      if object_place[object]=nowhere then
        begin
          write_message('I see something!!!');
          object_place[object] := your_place;
        end
      else if messg='' then
        I_see_nothing_special
      else
        write_message( messg )
    end;
end;


procedure not_yet_but_maybe_later;
(*==============================*)
begin
  write_message('Not yet but maybe later!');
end;


procedure sorry_no_money;
(*=====================*)
begin
  write_message('Sorry -- no money!!');
end;


function is_here ( obj : objects ) : boolean;
(*=========================================*)
begin
  with game_position do
    is_here := object_place[obj] = your_place;
end;


function is_carried ( obj : objects ) : boolean;
(*============================================*)
begin
  with game_position do
    is_carried := object_place[obj] = youhavit;
end;


function you_are_in ( place : places ) : boolean;
(*=============================================*)
begin
  with game_position do
    you_are_in := your_place = place;
end;



function save_file_name( objnam : word_name_string ) : str25;
(*=========================================================*)
var i         : integer;
    file_name : str25;
begin
  file_name := 'SOFTP' + copy(objnam,1,3);
  repeat
    i := pos( ' ', file_name );
    if i>0 then
      delete( file_name, i, 1 );
  until i=0;
  if file_name='SOFTP' then
    file_name := 'SOFTPORN';
  save_file_name := file_name + '.SAV';
end;



procedure init_new_game;
(*====================*)

var yesno     : char;
    place     : places;
    direction : directions;
    i         : integer;

begin
  clrscr;
  cursor_to_bottom;
  writeln ('Welcome to SOFTPORN ADVENTURE!!'); newlines(2);
  write   ( 'Do you need instructions? (y/n) '); read_key( yesno, ['Y','N'] );
  if yesno='Y' then
    give_help
  else
    newlines(2);

  with game_position do
    begin

      line_from_kbd := '';

      object_place := orig_object_place;

      path := orig_path;

      for place:=first_place to last_place do
        place_visited[place] := false;

      your_place         := b_bar;

      objects_carried    := 0;
      TV_channel         := 0;
      money              := 10;   { $1000 }
      score              := 0;

      rope_in_use        := false;
      window_broken      := false;
      toilet_flushed     := false;
      called_555_0987    := false;
      called_555_6969    := false;
      called_555_0439    := false;
      rubber_worn        := false;
      hooker_fucked      := false;
      door_W_open        := false;
      radio_listened     := false;
      wine_ordered       := false;
      telephone_ringing  := false;
      telephone_answered := false;
      hole_peeped        := false;
      girl_2_fucked      := false;
      tied_to_bed        := false;
      drawer_open        := false;
      closet_open        := false;
      cabinet_open       := false;
      doll_inflated      := false;
      stool_climbed      := false;
      water_on           := false;
      pitcher_full       := false;
      seeds_planted      := false;
      seeds_watered      := false;
      apple_given        := false;
      candy_given        := false;
      flowers_given      := false;
      ring_given         := false;
      married_to_girl    := false;

    end;

end;      { Init new game }


procedure look_around;
(*==================*)
var objcount  : integer;
    obj       : objects;
    exits,
    exitcount : integer;
    exit      : directions;
    anyexit   : boolean;
    i,j,
    hpos,
    namelen   : integer;

begin
  with game_position do
    begin
      if not place_visited[your_place] then
        write_long_message( integer(your_place)+1 );
      if (your_place=p_pntpch) and called_555_0439 then
        begin
          if not telephone_answered and (random(4)=2) then
            telephone_ringing := true;
          if telephone_ringing then
            write_message('The telephone rings');
        end;
      place_visited[your_place] := true;
      newlines(2);

      gotoXY(1,1);
      clreol;
      writeln( place_name[your_place] );

      clreol;
      write( 'Items in sight are:  ' );
      hpos := 23;
      objcount := 0;
      for obj := first_object to last_object do
        begin
          if is_here(obj) then
            begin
              if objcount>0 then
                begin
                  write(', ');
                  hpos := hpos + 2;
                end;
              objcount := objcount + 1;
              namelen := length(object_name[obj]);
              if ( hpos + 3 + namelen ) > 80 then
                begin
                  writeln;
                  clreol;
                  write( '                     ' );
                  hpos := 23;
                end;
              write(object_name[obj]);
              hpos := hpos + namelen;
            end;
        end;
      if objcount=0 then
        writeln( 'Nothing interesting.')
      else
        writeln;

      clreol;
      write( 'Other areas are:  ');
      exitcount := 0;
      for exit := first_direction to last_direction do
        if path[your_place,exit] <> nowhere then
          exitcount := exitcount + 1;
      exits := exitcount;
      if exits=0 then
        write('By magic!')
      else
        for exit := first_direction to last_direction do
          if path[your_place,exit] <> nowhere then
            begin
              if exitcount<exits then
                begin
                  if exitcount>1 then
                    write(', ')
                  else if exits>1 then
                    write(' and ');
                end;
              exitcount := exitcount - 1;
              write( direction_name[exit]);
            end;

      writeln;
      clreol;
      for i:=1 to 79 do
        write('=');
      writeln;
      clreol;

      cursor_next_to_bottom;

    end;  { with }

end;  { look_around }



procedure take_inventory;
(*=====================*)
var objcount  : integer;
    obj       : objects;

begin
  with game_position do
    begin
      writeln;
      writeln( 'I''m carrying: ');
      objcount := 0;
      for obj := first_object to last_object do
        begin
          if is_carried(obj) then
            begin
              objcount := objcount + 1;
              writeln(object_name[obj]);
            end;
        end;
      if objcount=0 then writeln('Nothing') else writeln;
    end;

end;  { take_inventory }



procedure replace( object, replacement : str10; target : str120 );
(*==============================================================*)
var i : integer;
begin
  if object<>replacement then
    repeat
      i := pos( object, target );
      if i>0 then
        begin
          delete( target, i, length(object) );
          insert( replacement, target, i );
        end;
    until i=0;
end;  { replace }


procedure replace_with_space( object : str10; target : str120 );
(*============================================================*)
begin
  replace( object, ' ', target );
end;  { replace_with_space }


procedure remove_leading_spaces( var str : str120 );
(*================================================*)
var i             : integer;
    leading_space : boolean;
begin
  repeat
    i := length(str);
    leading_space := (i>0) and (str[1]=' ');
    if leading_space then
      delete( str,1,1);
  until not leading_space;
end;  { remove_leading_spaces }


procedure remove_leading_spaces_and_periods( var str : str120 );
(*============================================================*)
var i                    : integer;
    leading_space_period : boolean;
begin
  repeat
    i := length(str);
    leading_space_period := (i>0) and ( (str[1]=' ') or (str[1]='.') );
    if leading_space_period then
      delete( str,1,1);
  until not leading_space_period;
end;  { remove_leading_spaces_and_periods }


procedure remove_trailing_spaces( var str : str120 );
(*=================================================*)
var i              : integer;
    trailing_space : boolean;
begin
  repeat
    i := length(str);
    trailing_space := (i>0) and (str[1]=' ');
    if trailing_space then
      delete( str,i,1);
  until not trailing_space;
end;  { remove_trailing_spaces }


procedure remove_multiple_spaces( var str : str120 );
(*=================================================*)
var i : integer;
begin
  repeat
    i := pos( '  ', str );
    if i>0 then
      delete( str, i, 1 );
  until i=0;
end;  { remove_multiple_spaces }


procedure expand_abbreviations( var str : str120 );
(*===============================================*)
var ch1 : char;
    str4 : string[4];
    i    : integer;
begin
  str4 := copy( str+'    ', 1, 4 );
  for i:=1 to length(str4) do
    str4[i] := upcase(str4[i]);
  if str4 = 'INVE' then
    str := 'I';
  if length(str)=1 then
    begin
      ch1 := upcase(str[1]);
           if ch1='I' then str := 'TAKE INVE'
      else if ch1='N' then str := 'GO NORT'
      else if ch1='S' then str := 'GO SOUT'
      else if ch1='E' then str := 'GO EAST'
      else if ch1='W' then str := 'GO WEST'
      else if ch1='U' then str := 'GO UP'
      else if ch1='D' then str := 'GO DOWN'
      else if ch1='L' then str := 'LOOK';
    end;
end;  { expand abbreviations }


procedure add_definite_article_to( var full_noun : str25 );
(*=======================================================*)
begin
  if full_noun[1] in vowels then
    full_noun := ' an ' + full_noun
  else
    full_noun := ' a '  + full_noun;
end;


procedure split_up_in_verb_and_noun( command : str120;
                   var verb, noun : word_name_string;
                   var full_verb, full_noun : str25 );
(*==================================================*)
const spaces = '    ';
var i, p, k   : integer;
    glue_word : boolean;
    word      : word_name_string;
    full_word : str25;
begin
  verb := spaces;
  noun := spaces;
  full_verb := '';
  full_noun := '';
  remove_leading_spaces(command);
  for i:=1 to 2 do
    begin
      repeat
        p := pos( ' ', command );
        if p=0 then
          begin
            full_word := command;
            command := '';
          end
        else
          begin
            full_word := copy ( command, 1, p-1 );
            delete( command, 1, p );
            remove_leading_spaces(command);
          end;
        word := full_word + spaces;
        for k:=1 to length(word) do
          word[k] := upcase(word[k]);
        glue_word := false;
        for k:=1 to gl_words do
          if word=glue_words[k] then
            glue_word := true;
      until not glue_word;
      if i=1 then
        begin
          verb := word;
          full_verb := full_word;
        end
      else
        begin
          noun := word;
          full_noun := full_word;
        end;
    end;  { for i:=1 to 2 do }
  for i:=1 to syn_verbs do
    if verb=syn_verb[i].orig then
      verb := syn_verb[i].repl;
  for i:=1 to syn_nouns do
    if noun=syn_noun[i].orig then
      noun := syn_noun[i].repl;
end;  { split up in verb and noun }



procedure read_and_parse_command( var verb, noun : word_name_string;
                                  var full_verb, full_noun : str25 );
(*=================================================================*)

var i, sppos   : integer;
    command    : str120;
    command_ok : boolean;

begin

  repeat

    if line_from_kbd='' then
      begin
        repeat
          look_around;
          repeat
            writeln;
            write( 'What shall I do? ' );
            readln( line_from_kbd );
            if line_from_kbd='' then
              write_message('Beg pardon?');
          until line_from_kbd<>'';
          repeat
            i := pos( '-', line_from_kbd );
            if i>0 then
              delete( line_from_kbd, i, 1 );
          until i=0;
          for i := 1 to length(line_from_kbd) do
            begin
              if line_from_kbd[i] in [ '!', '?', ',' ] then
                line_from_kbd[i] := '.'
              else if line_from_kbd[i] in [ '!'..'-', '/', ':'..'?' ] then
                line_from_kbd[i] := ' ';
            end;
          remove_leading_spaces_and_periods(line_from_kbd);
          remove_trailing_spaces(line_from_kbd);
          remove_multiple_spaces(line_from_kbd);
          if line_from_kbd=' ' then
            line_from_kbd := '';
          if line_from_kbd='' then
            I_cant_do_that;
        until line_from_kbd<>'';
      end;


    i := pos( '.', line_from_kbd );
    if i>0 then
      begin
        command := copy( line_from_kbd, 1, i-1 );
        delete( line_from_kbd, 1, i );
        remove_leading_spaces_and_periods( line_from_kbd );
        remove_trailing_spaces( command );
      end
    else
      begin
        command := line_from_kbd;
        line_from_kbd := '';
      end;

    expand_abbreviations(command);

    repeat
      i := pos( '555', command );
      if i>0 then
        delete( command, i, 3 );
    until i=0;

    split_up_in_verb_and_noun( command, verb, noun, full_verb, full_noun );

    command_ok := verb <> '    ';

    if noun='LADY' then
      begin
        write_message('That''s no Lady!!!  That''s my sister!!!!');
        command_ok := false;
      end
    else if verb='SAY ' then
      begin
        write_message('OK');
        writeln( copy( command, 5, 120 ) );
        command_ok := false;
      end
    else if (verb='TKAE') or (verb='TAEK') then
      begin
        write_message('Learn to spell, idiot!!!');
        command_ok := false;
      end;

  until command_ok;


end;    { read_and_parse_command }

