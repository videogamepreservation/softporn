{ Softporn Adventure, include file 4 }



go :
{========}
  begin

    if tied_to_bed then
      write_message('But I''m tied to the bed!!!!!')

    else if not no_direction then
      begin

        if (your_place=b_bedrm) and (direction=north) and
           (not hooker_fucked) then
          write_message
            ('The Hooker says:  ''Don''t go there ... do me first!!''')

        else if (your_place=c_hallwy) and (direction=south) and
                (not married_to_girl) then
          write_message('The door is locked shut!')

        else if (your_place=d_entrnc) and (direction=west) and
                (not door_W_open) then
          write_message('The door is closed!')

        else if (your_place=b_backrm) and (direction=up) and
                (TV_channel<>6) then
          begin
            if (money<20) or (not is_carried(_wallet)) then
              write_message('The Pimp says I can''t until I get $2000')
            else if hooker_fucked then
              write_message
                ('The Pimp says ''No -- the hooker can''t take it anymore!''')
            else
              begin
                write_message('The Pimp takes $2000 and says OK');
                money := money - 20;
                your_place := b_bedrm;
              end
          end

        else if (your_place=b_balcny) and (direction=west) and
                (not rope_in_use) then
          falling_down

        else
          begin
            new_place := path[your_place,direction];
            if new_place <> nowhere then
              begin
                your_place := new_place;
              end
            else
              I_cant_go_that_way;
          end;
      end

    else
      I_cant_do_that

  end; {go}


hail :
{========}
  begin

    if noun<>_taxi then
      write_message('Who are you kidding?  You''re pulling at straws, fool!!')

    else if not (your_place in [ b_street, c_street, d_street ]) then
      write_message('I''m not in the street, fool!!')

    else
      begin
        write_long_message( 36 );
        readln( taxi_destination );
        while (length(taxi_destination)>0) and (taxi_destination[1]=' ') do
          delete( taxi_destination, 1, 1 );
        for i:=1 to length(taxi_destination) do
          taxi_destination[i] := upcase(taxi_destination[i]);
        taxi_destination := copy( taxi_destination+' ', 1, 4 );
        if taxi_destination = 'DISC' then
          new_place := d_street
        else if taxi_destination = 'CASI' then
          new_place := c_street
        else if taxi_destination = 'BAR ' then
          new_place := b_street
        else
          new_place := nowhere;
        if new_place in [your_place,nowhere] then
          write_message('Huh? - Hail another!')
        else if is_carried(_wine) then
          begin
            wine_in_taxi;
            your_place := new_place;
            object_place[_wine] := nowhere;
            objects_carried := objects_carried - 1;
          end
        else
          begin
            write_message('We arrive and I get out.');
            your_place := new_place;
          end;
      end;

  end; {hail}


take : { get, grab }
{========}
  begin

    if noun=_inventory then
      begin
        anything_carried := false;
        for _noun:=first_object to last_object do
          if is_carried(_noun) then
            begin
              if not anything_carried then
                write_message('I''m carrying the following:');
              anything_carried := true;
              write(object_name[_noun]);
              if (_noun=_wallet) and (money>0) then
                writeln(' with $',money,'00')
              else
                writeln;
            end;
        if not anything_carried then
          write_message('I''m not carrying anything!!');
      end

    else if noun=_off then
      write_message('You''re not a bird, fool!!')

    else if noun=_all then
      begin
        write_message('You hog!!!');
        delay(300);
        writeln;
        for _noun:=first_object to last_object do
          if is_here(_noun) then
            begin
              write(object_name[_noun],': ');
              if objects_carried >= max_carried then
                writeln('I''m carrying too much!!!')
              else if _noun in takeable_objects then
                begin
                  if (your_place=d_phrmcy) and
                     (_noun in [_magazine,_rubber]) then
                    begin
                      writeln('The man says ''Shoplifter!!'' and shoots me');
                      purgatory;
                    end
                  else
                    begin
                      object_place[_noun] := youhavit;
                      objects_carried := objects_carried + 1;
                      if _noun=_water then pitcher_full := true;
                      if (_noun=_pitcher) and pitcher_full then
                        object_place[_water] := youhavit;
                      writeln('Taken');
                    end
                end
              else
                cant_do_that;
            end;
        end

    else if is_carried(noun) then
      I_already_have_it

    else if not is_here(noun) then
      find_me_one

    else if objects_carried >= max_carried then
      write_message('I''m carrying too much!!!')

    else if not (noun in takeable_objects) then
      I_cant_do_that

    else if (your_place=d_phrmcy) and ( noun in [_magazine,_rubber] ) then
      begin
        write_message('The man says ''Shoplifter!!'' and shoots me');
        purgatory;
      end

    else if (noun=_water) and (not is_carried(_pitcher)) then
      write_message('Get me the pitcher so I don''t spill it!')

    else if (noun=_candy) and (your_place=b_bedrm) and (not hooker_fucked) then
          write_message
            ('The Hooker says:  ''Don''t take it ... do me first!!''')

    else if (noun=_rope) and rope_in_use then
      write_message('It is tied to the balcony')

    else
      begin
        OK;
        object_place[noun] := youhavit;
        objects_carried := objects_carried + 1;
        if noun=_water then pitcher_full := true;
        if (noun=_pitcher) and pitcher_full then
          object_place[_water] := youhavit;
      end

  end; {take}


drop : { leave, plant (seeds), give }
{========}
  begin

    if noun in [_inventory,_taxi,_on,_off] then
      huh

    else if noun=_all then
      begin
        anything_carried := false;
        writeln;
        for _noun:=first_object to last_object do
          if is_carried(_noun) then
            begin
              anything_carried := true;
              writeln(object_name[_noun],': Dropped');
              object_place[_noun] := your_place;
              objects_carried := objects_carried - 1;
            end;
        if not anything_carried then
          writeln('I did''t carry anything!!');
      end

    else if not is_carried(noun) then
      I_dont_have_it

    else
      begin
        object_place[noun] := your_place;
        objects_carried := objects_carried - 1;
        if (noun=_pitcher) and pitcher_full then
          object_place[_water] := your_place
        else if noun=_rubber then
          rubber_worn := false
        else if (your_place=d_disco) and (is_here(_girl)) and
           (noun in [_candy,_flowers,_ring]) then
          begin
            case noun of
              _candy:
                begin
                  write_message('She smiles and eats a couple!!');
                  candy_given := true;
                end;
              _flowers:
                begin
                  write_message
                     ('She blushes profusely and puts them in her hair!');
                  flowers_given := true;
                  object_place[_flowers] := nowhere;
                end;
              _ring:
                begin
                  write_message('She blushes and puts it in her purse.');
                  ring_given := true;
                  object_place[_ring] := nowhere;
                end;
            end; { case noun of }
            if candy_given and flowers_given and ring_given then
              begin
                write_message
                  ('She says: ''See you at the Marriage Center!!''');
                object_place[_girl] := c_marryc;
              end;
          end
        else if is_here(_bum) and (noun=_wine) then
          begin
            if object_place[_knife]=nowhere then
              begin
                bum_tells_story;
                object_place[_knife] := your_place;
              end
            else
              write_message('The bum mutters ' +
                    '''That stuff made me puke!!  Get out of here!!!''');
          end
        else if is_here(_businessman) and (noun=_whiskey) and
                (object_place[_control_unit]=nowhere) then
          begin
            write_message('The guy gives me a TV controller!!');
            object_place[_control_unit] := your_place;
          end
        else if is_here(_blonde) and (noun=_pills) then
          begin
            write_long_message( 57 );
            object_place[_blonde] := nowhere;
            object_place[_pills] := nowhere;
          end
        else if (noun=_apple) and (your_place=p_jacuzi) and is_here(_girl) then
          begin
            write_long_message( 50 );
            apple_given := true;
          end
        else
          OK;
      end;

  end; {drop}


look : { search, examine, read, watch }
{========}
  begin

    if no_object then
      write_long_message( integer(your_place)+1 )

    else if noun=_all then
      write_message('That''s too much, one item at a time, please!!')

    else if noun in [_inventory,_on,_off] then
      huh

    else if (not is_here(noun)) and
            (not is_carried(noun)) then
      find_me_one

    else
      case noun of

      _desk:
        begin
          if drawer_open then
            I_see_something(_newspaper,'')
          else
            write_message('It''s drawer is shut');
        end;

      _washbasin:
         I_see_something(_ring,'Dead cockroaches...');

      _graffiti:
        look_graffiti;

      _mirror:
        write_message('There''s a pervert looking back at me!!');

      _toilet:
        write_message('Hasn''t been flushed in ages!  Stinks!!!');

      _businessman:
        write_message('He looks like a whiskey drinker to me!!');

      _button:
        write_message('Says Push.');

      _bartender:
        write_message('He''s waiting for me to buy something!');

      _pimp:
        begin
          write_message('He''s wearing a button proclaiming -- ' +
                        'Support your local Pimp, gimme $2000!!!');
        end;

      _hooker:
        write_long_message( 31 );

      _billboard:
        write_long_message( 63 );

      _TV:
        begin
         if not is_carried(_control_unit) then
           write_message('To watch TV, I need the remote control unit!!')
         else if not hooker_fucked then
           write_message('The Pimp says I can''t watch TV')
         else
           watch_TV( TV_channel );
        end;

      _slot_machines:
        write_message('Playing them might be more fun....');

      _ashtray:
        I_see_something(_passcard,'');

      _blonde:
        write_long_message( 40 );

      _bum:
        write_message
          ('He grumbles -- I''ll tell you a story for a bottle of wine.....');

      _peephole:
        if hole_peeped then
          write_message ('All windows at the hotel across the road ' +
                         'have their curtains shut.')
        else
          begin
            write_long_message( 55 );
              hole_peeped := true;
          end;

      _door_west:
        begin
          if door_W_open then
            write_message('The door is open')
          else
            begin
              write_message('The sign on the door says ');
              writeln('''Entry by showing passcard - ' +
                       'Club members and their guests only!''');
            end
        end;

      _waitress:
        write_message('She ignores you!');

      _telephone:
        begin
          if your_place=d_telbth then
            write_message('A number is there - Call 555-6969 for a good time!')
          else
            I_see_nothing_special
        end;

      _closet:
        begin
          if closet_open then
            I_see_something(_doll,'It''s open')
          else
            write_message('It''s closed')
        end;

      _sink:
        write_message
            ('The sign over the sink says ''Water on or off to operate''');

      _elevator:
        write_message('It''s doors are closed');

      _dealer:
        write_message('He''s waiting for me to play');

      _cabinet:
        begin
          if stool_climbed then
            begin
              if cabinet_open then
                I_see_something(_pitcher,'It''s open')
              else
                write_message('It''s closed');
            end
          else
            I_see_nothing_special
        end;

      _bushes:
        write_message('Entering them would be kinky!!!!');

      _tree:
        I_see_something(_apple,'');

      _sign:
        write_message('It says ''Hail taxi here''');

      _girl:
        begin
          if your_place=p_jacuzi then
            write_long_message( 35 )
          else if (your_place=d_disco) or (your_place=c_marryc) then
            write_long_message( 34 )
          else
            write_message('She slaps me and yells ''Pervert!!!!!''')
        end;

      _newspaper:
        begin
          if is_carried(_newspaper) then
            write_long_message( 32 )
          else
            I_dont_have_it
        end;

      _garbage:
        I_see_something(_apple_core,'');

      _flowers:
        write_message('They look beautiful!!!');

      _apple_core:
        I_see_something(_seeds,'');

      _pills:
        begin
          write_message('The label on the bottle says');
          writeln('''Want to drive someone crazy with lust??  Try this!!!!''');
        end;

      _plant:
        begin
          if object_place[_bushes]=nowhere then
            begin
              write_message('There''s a group of bushes behind it!!');
              object_place[_bushes] := your_place;
            end
          else
            I_see_nothing_special
        end;

      _radio:
        write_message('Maybe I should listen...');

      _magazine:
        begin
          if is_carried(_magazine) then
            write_long_message( 33 )
          else
            I_dont_have_it
        end;

      _rubber:
        begin
          if is_carried(_rubber) then
            write_message('It''s ' + rubber_color + ', ' + rubber_flavor +
              '-flavored, ' + rubber_lubricated + ', and ' + rubber_ribbed )
          else
            I_dont_have_it
        end;

      _wallet:
        begin
          if money>0 then
            begin
              writeln;
              writeln('It contains $',money,'00.');
            end
          else
            write_message('It''s empty');
        end;

      _doll:
        begin
          if doll_inflated then
            write_message('It''s inflated')
          else
            write_message('It''s rolled up in a little ball');
        end;

      _pitcher:
        begin
          if pitcher_full then
            write_message('It''s full of water')
          else
            write_message('It''s empty');
        end;

      _rack:
        I_see_something(_magazine,'');

      _curtain:
        write_message('It''s on the east wall');

      else
        I_see_nothing_special;

      end; {case noun of}

  end; {look}


flush :
{========}
  begin

    if not is_here(noun) then
      find_me_one

    else if noun=_toilet then
      begin
        write_long_message( 69 );
        delay(300);
        write_message('I''m dead from the germs!!');
        purgatory;
      end
    else
      I_cant_do_that

  end; {flush}


open : { pull }
{========}
  begin

    if not is_here(noun) then
      find_me_one

    else case noun of

      _window:
        write_message('Won''t budge');

      _desk:
        _open(drawer_open);

      _door_west:
        begin
          if door_W_open then
            write_message('It''s already open!!')
          else
            begin
              write_message
                 ('A voice asks ''Passcard?''  I search in my pockets and...');
              if is_carried(_passcard) then
                begin
                  writeln('I have it!  The door opens!');
                  door_W_open := true;
                  path[d_entrnc,west] := d_disco;
                end
              else
                writeln('I don''t have it!!');
            end;
        end;

      _curtain:
        write_message('It seems to be remotely controlled');

      _elevator:
        write_message('Push the button to open elevator');

      _closet:
        _open(closet_open);

      _cabinet:
        if stool_climbed then
          _open(cabinet_open)
        else
          write_message('I can''t reach it!!');

      else
        I_cant_do_that

    end;

  end; {open}


inflate :
{========}
  begin

    if noun=_doll then
      begin
        if is_carried(_doll) then
          begin
            if doll_inflated then
              write_message('You''ve already inflated it, stupid!!')
            else
              begin
                OK;
                doll_inflated := true;
              end;
          end
        else if is_here(_doll) then
          write_message('I can''t unless I''m holding it close')
        else
          find_me_one;
      end

    else
      write_message('But the prime rate is already 257%!!');

  end; {inflate}


play :
{========}
  begin

    if not is_here(noun) then
      find_me_one

    else if noun=_slot_machines then
      begin
        if is_here(_slot_machines) then
          begin
            if (money>0) and (is_carried(_wallet)) then
              play_slot( money )
            else
              sorry_no_money
          end
        else
          write_message('OK, show me your slot....');
      end

    else if noun=_cards then
      begin
        if your_place=c_21room then
          begin
            if (money>0) and (is_carried(_wallet)) then
              play_21( money )
            else
              sorry_no_money
          end
        else
          not_yet_but_maybe_later;
      end

    else
      write_message('Playful bugger, eh??');

  end; {play}





