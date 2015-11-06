{ Softporn Adventure, include file 5 }



press : { push }
{========}
  begin

    if noun=_button then
      begin
        if your_place=b_bar then
          begin
            writeln;
            write('A voice says  ''What''s the password?''  (one word) ');
            readln(password);
            for i:=1 to length(password) do
              password[i] := upcase(password[i]);
            if copy(password,1,6)='BELLYB' then
              begin
                write_message('The curtain pulls back!!');
                path[b_bar,east] := b_backrm;
              end
            else
              write_message('Wrong!!');
          end
        else if your_place in [ c_htdesk, p_pntfoy ] then
          begin
            if is_here(_blonde) then
              write_message('The blonde says  ''You can''t go there!''')
            else
              begin
                write_long_message( 37 );
                if your_place=c_htdesk then
                  your_place := p_pntfoy
                else
                  your_place := c_htdesk;
              end;
          end
        else
          not_yet_but_maybe_later
      end {press/push button}

    else
      write_message('Pushy chump, eh???');

  end; {press}


enter :
{========}
  begin

    if not is_here(noun) then
      find_me_one

    else if noun=_bushes then
      your_place := p_garden

    else if noun=_window then
      begin
        if window_broken then
          your_place := b_inroom
        else
          not_yet_but_maybe_later;
      end

    else if noun=_door_west then
      begin
        if door_W_open then
          your_place := d_disco
        else
          write_message('The door is closed')
      end

    else if noun=_elevator then
      write_message('Push the button to enter the elevator')

    else
      I_cant_do_that

  end; {enter}


eat :
{========}
  begin

    if (not is_here(noun)) and (not is_carried(noun)) then
      find_me_one

    else if noun in [ _blonde, _waitress, _hooker, _girl ] then
      begin
        write_long_message( 38 );
        purgatory;
      end

    else if noun=_mushroom then
      begin
        write_long_message( 64 );
        your_place := places( random(3) );
        delay(600);
        write_long_message( integer(your_place)+1 );
      end

    else if noun in [ _garbage, _apple_core ] then
      write_message('Too moldy!')

    else if noun=_apple then
      write_message('Sorry ... not hungry!')

    else if noun=_pills then
      begin
        write_long_message( 56 );
        purgatory;
      end

    else
      write_message('Tastes awful!');

  end; {eat}


drink :
{========}
  begin

    if not is_carried(noun) then
      I_dont_have_it

    else
      begin
        case noun of
          _whiskey: write_message
            ('This stuff is rot-gut!  Give it to someone ... I don''t want it.');
          _beer:    write_message('Heh...heh...hey!!!!  This stuff''s OK!');
          _wine:    write_message('Sour grapes....');
          _water:   write_message('Thanks!');
          else      write_message('Get your head examined!!!!');
        end;
        if noun in [_beer,_water] then
          begin
            object_place[noun] := nowhere;
            objects_carried := objects_carried - 1;
          end;
      end;

  end;


buy : { order }
{========}
  begin

    if (money<1) or (not is_carried(_wallet)) then
      sorry_no_money
    else

      case noun of

        _whiskey,_beer:
          begin
            if (your_place<>b_bar) then
              not_yet_but_maybe_later
            else
              begin
                if object_place[noun]<>nowhere then
                  write_message('Sorry ... all out!')
                else
                  begin
                    write_message ('I give the bartender $100 and ' +
                                   'he places it on the bar.');
                    money := money - 1;
                    object_place[noun] := your_place;
                  end;
              end
          end;

        _wine:
          begin
            if (your_place<>d_disco) then
              not_yet_but_maybe_later
            else
              begin
                if object_place[noun]<>nowhere then
                  write_message('All out!')
                else
                  begin
                    write_message
                        ('The waitress takes $100 and says she''ll return');
                    delay(3000);
                    write_message('Poor service!!!');
                    delay(2000);
                    money := money - 1;
                    object_place[noun] := your_place;
                  end;
              end
          end;

        _rubber,_magazine:
          begin
            if (your_place<>d_phrmcy) then
              not_yet_but_maybe_later
            else
              begin
                if is_here(noun) then
                  begin
                    if noun=_rubber then
                      buy_rubber
                    else
                      write_message('He takes $100 and gives me the magazine');
                    money := money - 1;
                    object_place[noun] := youhavit;
                  end
                else
                  write_message('Sorry!!! --- sold out!');
              end
          end;

        _hooker:
          begin
            if is_here(_hooker) then
              write_message('You''ve already paid the pimp, stupid!!!!')
            else
              find_me_one;
          end;

        else
          write_message('Money can''t buy everything!!!!');

      end; {case}

  end; {buy}


climb :
{========}
  begin

    if noun=_stool then
      begin
        if is_here(_stool) then
          begin
            OK;
            stool_climbed := true;
          end
        else
          write_message('It''s not on the floor here!');
      end

    else if is_here(noun) or is_carried(noun) then
     I_cant_do_that

    else
      find_me_one;

  end; {climb}


water :
{========}
  begin

    if noun in [_on,_off] then
      begin
        if not is_here(_sink) then
          write_message('Find a working sink!')
        else
          begin
            water_on := noun=_on;
            if water_on then
              begin
                write_message('Water is running in the sink');
                object_place[_water] := your_place;
              end
            else if not pitcher_full then
              begin
                OK;
                object_place[_water] := nowhere;
              end;
          end;
      end

    else if not is_carried(_water) then
      write_message('I have no water!')

    else if not is_here(noun) then
      find_me_one

    else if noun=_seeds then
      begin
        object_place[_water] := nowhere;
        pitcher_full := false;
        if your_place=p_garden then
          begin
            write_message('A tree sprouts!!');
            object_place[_tree] := your_place;
            object_place[_seeds] := nowhere;
          end
        else
          write_message('The seeds need better soil to grow.');
      end

    else
      begin
        write_message('It pours into the ground.');
        object_place[_water] := nowhere;
        pitcher_full := false;
      end;

  end; {water}


fill :
{========}
  begin

    if not (noun=_pitcher) then
      I_cant_do_that

    else if not is_carried(_pitcher) then
      write_message('I don''t have it!')

    else if not is_here(_sink) then
      write_message('Find a working sink!!')

    else if not water_on then
      write_message('No water!!')

    else if pitcher_full then
      write_message('The pithcer is already full!')

    else
      begin
        OK;
        pitcher_full := true;
      end

  end; {fill}


pour :
{========}
  begin

    if not (noun=_water) then
      I_cant_do_that

    else if not is_carried(_pitcher) then
      write_message('You have nothing to pour it with!')

    else if not pitcher_full then
      write_message('The pitcher is empty.')

    else if (your_place<>p_garden) or (not is_here(_seeds)) then
      write_message('It pours into the ground.')

    else
      begin
        write_message('A tree sprouts!!');
        object_place[_tree] := your_place;
      end
  end; {pour}


listen :
{========}
  begin

    if (not is_here(noun)) and (not is_carried(noun)) then
      find_me_one

    else if noun=_radio then
      begin
        if is_carried(_radio) then
          begin
            if radio_listened then
              write_message('Punk rock!!!!!')
            else
              begin
                write_message('An advertisement says  ' +
                            '''Call 555-0987 for all your liquor needs!!!!''');
                radio_listened := true;
              end;
          end
        else
          write_message('Take it and put it next to my ear!');
      end

    else
      write_message('Quiet as a mouse in heat!');

  end; {listen}


close :
{========}
  begin

    if not is_here(noun) then
      find_me_one

    else case noun of

      _desk:
        begin
          _close(drawer_open);
          if is_here(_newspaper) then
            object_place[_newspaper] := nowhere;
        end;

      _closet:
        begin
          _close(closet_open);
          if is_here(_doll) then
            object_place[_doll] := nowhere;
        end;

      _cabinet:
        if stool_climbed then
          begin
            _close(cabinet_open);
            if is_here(_pitcher) then
              object_place[_pitcher] := nowhere;
          end
        else
          write_message('I can''t reach it!');

      _door_west:
        begin
          _close(door_W_open);
          path[d_entrnc,west] := nowhere;
        end;
      else
        I_cant_do_that;

    end;

  end; {close}


jump :
{========}
  begin

    if your_place in [ b_balcny, b_wledge ] then
      falling_down

    else
      write_message('Whoooopeeeee!!!');

  end; {jump}




