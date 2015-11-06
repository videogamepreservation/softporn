{ Softporn Adventure, include file 6 }



marry :
{========}
  begin

    if noun<>_girl then
      write_message('No way, weirdo!!')

    else if not is_here(_girl) then
      write_message('No girl!!')

    else if your_place<>c_marryc then
      not_yet_but_maybe_later

    else if (money<30) or (not is_carried(_wallet)) then
      begin
        if (money<20) or (not is_carried(_wallet)) then
          write_message( 'The girl says: ' +
              '''But you''ll need $2000 for the honeymoon suite!''');
        write_message('The preacher says ''I''ll need $1000 too!!''');
      end
    else
      begin
        write_long_message( 66 );
        money := money - 30;
        object_place[_girl] := c_hmoons;
        married_to_girl := true;
        path[c_hallwy,south] := c_hmoons;
      end;

  end; {marry}


fuck : { seduce, rape, screw }
{========}
  begin

    if (not is_here(noun)) and (not is_carried(noun)) and (noun<>_you) then
      find_me_one

    else case noun of

      _hooker:
        begin
          if hooker_fucked then
            write_message('She can''t take it any more!!!!')
          else
            begin
              if rubber_worn then
                begin
                  hooker_fucked := true;
                  score := score + 1;
                  write_long_message( 51 )
                end
              else
                begin
                  write_message('Oh no!!! ' +
                    'I''ve got the dreaded atomic clap!!! I''m dead!!');
                  purgatory;
                end
            end;
        end;

      _doll:
        begin
          if is_carried(_doll) then
            if doll_inflated then
              begin
                write_long_message( 52 );
                object_place[_doll] := nowhere;
                objects_carried := objects_carried - 1;
              end
            else
              write_message('Inflate it first -- stupid!!!')
          else
            write_message('I can''t unless I''m holding it close');
        end;

      _girl:
        begin
          case your_place of
            c_hmoons:
              begin
                if wine_ordered then
                  begin
                    write_long_message( 54 );
                    girl_2_fucked := true;
                    score := score + 1;
                    tied_to_bed := true;
                    object_place[_girl] := p_jacuzi;
                    object_place[_rope] := your_place;
                  end
                else
                  write_message('She says  ''Get me wine!!!  I''m nervous!!''');
              end;
            p_jacuzi:
              begin
                if apple_given then
                  begin
                    score := score + 1;
                    write_long_message( 53 );
                    game_ended := true;
                  end
                else
                  not_yet_but_maybe_later
              end;
            else  not_yet_but_maybe_later
          end; { case your_place of }
        end;

      _bartender:
        begin
          write_message('He jumps over the bar and kills me!!');
          purgatory;
        end;

      _you:      write_message('Not tonight -- I have a headache!!');
      _waitress: write_message
                ('She kicks me in the groin and says ''Wise up - Buster!!''');
      _blonde:   write_message('She says ''I''m working! Leave me alone!!''');
      _pimp:     write_message('He says ''You''ll never have enough money ' +
                               'for me - fool!''.  I guess he''s gay!');
      _bum:      write_message('To do that I need vaseline!!');
      _businessman: write_message('No way!!!  You''re weird!!');
      _off:      write_message('Fuck off yourself, asshole!!!');

      else       write_message('Pervert!');

    end;  { case noun of }

  end; {fuck}


wear : { use }
{========}
  begin

    if (not is_here(noun)) and (not is_carried(noun)) and (noun<>_knife) then
      find_me_one

    else case noun of

      _rubber:
        begin
          write_message('It tickles!!');
          rubber_worn := true;
          object_place[_rubber] := youhavit;
        end;

      _toilet:
        begin
          write_message('.....I got those constipation blues..........');
          writeln('Ahhh...relief! Thanks');
        end;

      _bed:
        begin
          write_message('Ahhhhh.......sleep!!!!');
          delay(1000);
          writeln('No, I can''t sleep!  Have to find me a girl!!!!');
        end;

      _rope:
        begin
          if is_carried(_rope) then
            begin
              if your_place=b_balcny then
                begin
                  object_place[_rope] := your_place;
                  rope_in_use := true;
                  write_message('You tie the safety rope to the balcony');
                end
              else
                not_yet_but_maybe_later
            end
          else
            I_dont_have_it
        end;

      _passcard:
        begin
          if is_carried(_passcard) then
            begin
              if your_place=d_entrnc then
                begin
                  write_message('I show my passcard and the door opens');
                  path[d_entrnc,west] := d_disco;
                end
              else
                not_yet_but_maybe_later
            end
          else
            I_dont_have_it
        end;

      _knife:
        begin
          write_message('Let me see if I still have the knife!');
          delay(600);
          if is_carried(_knife) then
            begin
              if tied_to_bed then
                begin
                  write_message('I do and it worked! Thanks!');
                  tied_to_bed := false;
                end
              else
                begin
                  write_message('Samurai sex fiend!!!!!!!!!!!!!!!!!!!');
                  delay(600);
                  writeln('I stab myself in extacy!');
                  purgatory;
                end;
            end
          else
            I_dont_have_it
        end;

      else
        I_cant_do_that

    end;

  end; {wear/use}


answer :
{========}
  begin

    if not is_here(noun) then
      find_me_one

    else if noun<>_telephone then
      I_cant_do_that

    else if telephone_ringing then
      begin
        writeln;
        writeln('A girl says  ''Hi honey!  This is ',girl_name,'. Dear, why');
        writeln('don''t you forget this game and ',girl_do,' with me????');
        writeln('After all, your ',your_part,' has always turned me on!!!!');
        writeln('So bring a ',your_object,' and come play with my ',girl_part,
                '!''');
        writeln('She hangs up!');
        telephone_ringing := false;
        telephone_answered := true;
      end

    else
      write_message('It''s not ringing!');

  end; {answer}


call : { dial }
{========}
  begin

    if your_place=p_pntpch then
      write_message('This only takes incoming calls!!')

    else if (full_noun='6969') and (not called_555_6969) then
      begin
        writeln;
        writeln('A voice says ''Hello, please answer the questions ',
                'with one word answers:');
        write('What''s your favorite girls name?  '); readln(girl_name);
        write('Name a nice part of her anatomy!  ');  readln(girl_part);
        write('What do you like to do with her?  ');  readln(girl_do);
        write('And the best part of your body?   ');  readln(your_part);
        write('Finally, your favorite object?    ');  readln(your_object);
        writeln('He hangs up!');
        called_555_6969 := true;
        for i:=1 to length(girl_name) do
          girl_name[i] :=locase(girl_name[i]);
        girl_name[1] := upcase(girl_name[1]);
        for i:=1 to length(girl_part) do
          girl_part[i] :=locase(girl_part[i]);
        for i:=1 to length(girl_do) do
          girl_do[i] :=locase(girl_do[i]);
        for i:=1 to length(your_part) do
          your_part[i] :=locase(your_part[i]);
        for i:=1 to length(your_object) do
          your_object[i] :=locase(your_object[i]);
      end

    else if (full_noun='0439') and (not called_555_0439) then
      begin
        write_long_message( 67 );
        called_555_0439 := true;
      end

    else if (full_noun='0987') and married_to_girl and
            (not called_555_0987) then
      begin
        write_long_message( 68 );
        wine_ordered := true;
        called_555_0987 := true;
        object_place[_wine] := c_hmoons;
      end

    else
      write_message('Nobody answers');

  end; {call/dial}


break : { smash }
{========}
  begin

    if not is_here(noun) then
      find_me_one

    else if noun=_window then
      begin
        write_message('Let me see if I have a hammer');
        delay(400);
        if is_carried(_hammer) then
          begin
            write_message('The window smashes to pieces');
            path[b_wledge,south] := b_inroom;
          end
        else
          I_dont_have_it
      end

    else
      I_cant_do_that

  end; {break/smash}


cut :
{========}
  begin

    write_message('Let me see if I still have the knife!');
    delay(600);

    if is_carried(_knife) then
      begin
        if (noun=_rope) and tied_to_bed then
          begin
            write_message('I do and it worked! Thanks!');
            tied_to_bed := false;
          end
        else
          begin
            write_message('Samurai sex fiend!!!!!!!!!!!!!!!!!!!');
            delay(600);
            writeln('I stab myself in extacy!');
            purgatory;
          end;
      end

    else
      I_dont_have_it;

  end; {cut}


dance :
{========}
  begin

    writeln;
    for i:=1 to 3 do
      begin
        delay(500);
        writeln('Boogie Woogie!!!');
        delay(500);
        writeln('Yeh Yeh Yeh!!!');
      end;
    writeln('I got the steps, man!!');

  end; {dance}


kill :
{========}
  write_message('Try using a knife!!!');


pay :
{========}
  begin

    if not is_here(noun) then
      find_me_one

    else case noun of

      _pimp:
        begin
          if hooker_fucked then
            write_message('He says ''I don''t want your money - stud!''')
          else
            write_message('Try going up -- he''ll take the money then');
        end;

      _hooker:
        write_message('You already paid the Pimp, stupid!!');

      _blonde,_waitress,_girl:
        begin
          write_message('She yells ''I''m not a whore!!!'' and kills me!');
          purgatory;
        end;

      _preacher:
        write_message
            ('Bring a girl here to marry -- he''ll take the money then!');

      _businessman:
        write_message('He''s too drunk to do business right now!');

      _bartender:
        write_message('Buy something -- he''ll take the money then');

      _dealer:
        write_message('Why not play 21 instead?  You''ll lose anyway, fool!');

    else
      I_cant_do_that;

    end;

  end; {pay}


smoke :
{========}
  begin

    if noun=_plant then
      begin
        write_message('A cop beats me over the head!!!!');
        purgatory;
      end

    else
      I_cant_do_that;

  end; {smoke}


show :
{========}
  begin

    if noun=_passcard then
      begin
        if is_carried(_passcard) then
          begin
            if your_place=d_entrnc then
              begin
                write_message('I show my passcard and the door opens');
                path[d_entrnc,west] := d_disco;
              end
            else
              not_yet_but_maybe_later
          end
        else
          I_dont_have_it
      end

    else
      I_cant_do_that;

  end; {show}


smell :
{========}
  begin

    if (not is_here(noun)) and (not is_carried(noun)) then
      find_me_one

    else case noun of
      _blonde:  write_message('Hmmm.....nice!!!!');
      _hooker:  write_message('OK, who''s eating tuna fish?!?!?!');
      _toilet:  write_message('Arghhh...I''m going to puke!!!!!!');
      _plant:   write_message('Ahhh..chooo!!!!!!  I guess I''m allergic!');
      _garbage: write_message('Yechhhhh!!!!!');
      _flowers: write_message('Smells like perfume!!!');
      else      write_message('Smells OK');
    end;

  end; {smell}


help :
{========}
  begin
    give_help;
  end; {help}


kiss :
{========}
  begin
    write_message('Don''t do that!!!!  It gets me excited!!');
  end; {kiss}


stab :
{========}
  begin
    stab_someone;
  end; {stab}


quit : { stop, bye }
{========}
  begin
    game_ended := true;
  end; {quit}

show_score :
{========}
  begin
    writeln;
    writeln('Your score is ''',score,''' out of a possible ''3''');
  end; {show_score}


save :
{========}
  begin
    p := pos(' ',objnam);
    if p>0 then objnam := copy(objnam,1,p-1);
    assign( save_file, save_file_name(objnam) );
    rewrite( save_file );
    write( save_file, game_position );
    close( save_file );
    write_message( save_file_name(objnam) + ' saved' );
  end; {save}


restore :
{========}
  begin
    p := pos(' ',objnam);
    if p>0 then objnam := copy(objnam,1,p-1);
    {$I-}
    write_message( 'Restoring from ' + save_file_name(objnam) );
    writeln;
    assign( save_file, save_file_name(objnam) );
    reset( save_file );
    iores := IoResult;
    if iores=0 then
      begin
        read( save_file, game_position );
        iores := IoResult;
      end;
    {$I+}
    if iores=1 then
      write_message( save_file_name(objnam) + ' never saved' )
    else if (iores=$90) or (iores=$91) then
      write_message( save_file_name(objnam) + ' is bad' )
    else if iores<>0 then
      begin
        writeln;
        writeln( 'I/O error ', iores );
      end
    else
      write_long_message( integer(your_place) + 1 );
    close( save_file );
  end; {restore}


  else {anything else}
    I_cant_do_that;

