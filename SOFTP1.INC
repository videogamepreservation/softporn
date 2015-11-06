{ SoftPorn Adventure, include file # 1 (variable declarations) }


const   word_name_length   = 4;

type
  str10  = string[10];
  str15  = string[15];
  str25  = string[25];
  str80  = string[80];
  str120 = string[120];

  messg_string = str80;

  object_name_string    = string[30];
  place_name_string     = string[35];
  direction_name_string = string[6];
  verb_name_string      = string[10];
  word_name_string      = string[word_name_length];
  command_string        = string[80];
  synonym               = record
                            orig : word_name_string;
                            repl : word_name_string;
                          end;

  set_of_char  = set of char;

  directions = ( north, south, east, west, up, down, _no_direction );

  objects = (
    _desk,         _washbasin,  _graffiti,  _mirror,        _toilet,
    _businessman,  _button,     _bartender, _pimp,          _hooker,
    _billboard,    _preacher,   _TV,        _slot_machines, _cards,
    _ashtray,      _blonde,     _bed,       _bum,           _peephole,
    _door_west,    _waitress,   _table,     _telephone,     _closet,
    _sink,         _elevator,   _dealer,    _cabinet,       _bushes,
    _tree,         _window,     _sign,      _girl,          _newspaper,
    _ring,         _whiskey,    _beer,      _hammer,        _garbage,
    _flowers,      _apple_core, _seeds,     _candy,         _pills,
    _plant,        _passcard,   _radio,     _knife,         _magazine,
    _rubber,       _wine,       _wallet,    _doll,          _apple,
    _pitcher,      _stool,      _rope,      _rack,          _mushroom,
    _control_unit, _curtain,    _water,
    _taxi,         _inventory,  _all,       _on,            _off,
    _you,          _no_object   );

  places  = (
    (* ==================== BAR =================== *)
    b_hallwy, b_bathrm, b_bar,    b_street, b_backrm,
    b_g_dump, b_inroom, b_wledge, b_bedrm,  b_balcny,
    (* =================== CASINO ================= *)
    c_street, c_marryc, c_casino, c_21room, c_lobby,
    c_hmoons, c_hallwy, c_balcny, c_htdesk,
    (* =================== DISCO ================== *)
    d_telbth, d_disco,  d_street, d_entrnc, d_phrmcy,
    (* ================= PENTHOUSE ================ *)
    p_pntfoy, p_jacuzi, p_kitchn, p_garden, p_livrom,
    p_pntpch,
    (* ================= ELSEWHERE ================ *)
    youhavit, nowhere );



  verbs   = (
    go, hail, take, drop, look, flush, open, inflate, play,
    press, enter, eat, drink, buy, climb, water, fill, pour,
    listen, close, jump,
    marry, fuck, wear, answer, call, break, cut, dance,
    kill, pay, smoke, show, smell, help, kiss, stab, say, quit,
    show_score, save, restore, _no_verb );

{ True constants: }
const   max_carried        = 7;
        first_direction    = north;
        last_direction     = down;
        first_object       = _desk;
        last_object        = _no_object;
        first_place        = b_hallwy;
        last_place         = nowhere;
        first_verb         = go;
        last_verb          = _no_verb;

type    path_array = array[places,first_direction..last_direction] of places;


{ Typed constants = initialized variables: }
const
 bar_area       : set of places = [ b_hallwy .. b_balcny ];
 casino_area    : set of places = [ c_street .. c_htdesk ];
 disco_area     : set of places = [ d_telbth .. d_phrmcy ];
 penthouse_area : set of places = [ p_pntfoy .. p_pntpch ];

 public_places  : set of places =
 [ c_street, c_casino, c_21room, c_lobby, c_htdesk, d_street, d_entrnc ];

 takeable_objects : set of objects
  = [ _newspaper, _ring, _whiskey, _beer, _hammer, _garbage, _flowers,
      _apple_core, _seeds, _candy, _pills, _plant, _passcard, _radio, _knife,
      _magazine, _rubber, _wine, _wallet, _doll, _apple, _pitcher, _stool,
      _rope, _rack, _mushroom, _control_unit, _water ];


{Verbs that may be entered witout nouns }

stand_alone_verbs : set of verbs
        = [ look, jump, dance, help, quit, show_score, save, restore ];

{Verbs with special nouns }

special_verbs : set of verbs =
    [ take {inven}, hail {taxi}, call {number}, play {slot/21}, buy,
      save, restore ];


vowels : set of char = [ 'A', 'O', 'U', 'E', 'I', 'Y',
                         'a', 'o', 'u', 'e', 'i', 'y' ];



 direction_name : array[directions] of direction_name_string
           = ( 'North', 'South', 'East', 'West', 'Up', 'Down', 'No direction');

 object_name : array[objects] of object_name_string
       = ( 'A Desk',
           'A Washbasin',
           'Graffiti',
           'A Mirror',
           'A Toilet',
           'A Businessman',
           'A Button',
           'The Bartender',
           'A Big Dude!',
           'A Funky Hooker',
           'A Billboard',
           'A Preacher',
           'A TV',
           'Slot Machines',
           'Cards',
           'An Ashtray',
           'A Voluptous Blonde',
           'A Bed',
           'A Bum',
           'A Peep Hole',
           'A Door to the West',
           'A Waitress',
           'A Table',
           'A Telephone',
           'A Closet',
           'A Sink',
           'An Elevator',
           'A Dealer',
           'A Cabinet',
           'Bushes',
           'A Tree',
           'A Window',
           'A Sign',
           'A Girl',
           'A Newspaper',
           'A Wedding Ring',
           'A Shot of Whiskey',
           'A Beer',
           'A Hammer',
           'Garbage',
           'Flowers',
           'The Core of an Apple',
           'Seeds',
           'Candy',
           'Pills',
           'A Plant',
           'A Passcard',
           'A Radio',
           'A Pocket Knife',
           'AdventureBoy Magazine',
           'A Rubber',
           'A Bottle of Wine',
           'A Wallet',
           'An Inflatable Doll',
           'An Apple',
           'A Pitcher',
           'A Stool',
           'A Rope',
           'A Display Rack',
           'A Mushroom',
           'A Remote Control Unit',
           'A Curtain',
           'Water',
           'A Taxi',
           'Inventory',
           'All',
           'On',
           'Off',
           'Yourself',
           'No object'
         );

 orig_object_place : array[objects] of places  = (
     {A Desk}                   b_hallwy,
     {A Washbasin}              b_bathrm,
     {Graffiti}                 b_bathrm,
     {A Mirror}                 b_bathrm,
     {A Toilet}                 b_bathrm,
     {A Businessman}            b_hallwy,
     {A Button}                 c_htdesk,  {and p_pntfoy}
     {The Bartender}            b_bar,
     {A Big Dude!}              b_backrm,
     {A Funky Hooker}           b_bedrm,
     {A Billboard}              b_balcny,
     {A Preacher}               c_marryc,
     {A TV}                     b_backrm,
     {Slot Machines}            c_casino,
     {Cards}                    c_21room,
     {An Ashtray}               c_hallwy,
     {A Voluptous Blonde}       c_htdesk,
     {A Bed}                    c_hmoons,
     {A Bum}                    d_street,
     {A Peep Hole}              c_balcny,
     {A Door to the West}       d_entrnc,
     {A Waitress}               d_disco,
     {A Table}                  d_disco,
     {A Telephone}              d_telbth,
     {A Closet}                 p_livrom,
     {A Sink}                   p_kitchn,
     {An Elevator}              c_htdesk,  {and p_pntfoy}
     {A Dealer}                 c_21room,
     {A Cabinet}                p_kitchn,
     {Bushes}                   nowhere,   {seen behind bushes}
     {A Tree}                   nowhere,   {grown in garden}
     {A Window}                 b_wledge,
     {A Sign}                   b_street,  {and c_street and d_street}
     {A Girl}                   d_disco,   {c_marryc, c_hmoons, p_jacuzi}
     {A Newspaper}              nowhere,   {seen in drawer in b_hallwy}
     {A Wedding Ring}           nowhere,   {seen in washbasin in b_bathrm}
     {A Shot of Whiskey}        nowhere,   {bought in bar}
     {A Beer}                   nowhere,   {bought in bar}
     {A Hammer}                 p_garden,
     {Garbage}                  b_g_dump,
     {Flowers}                  b_hallwy,
     {The Core of an Apple}     nowhere,   {found in garbage}
     {Seeds}                    nowhere,   {found in apple core}
     {Candy}                    b_bedrm,
     {Pills}                    b_inroom,
     {A Plant}                  c_lobby,
     {A Passcard}               nowhere,   {found in ashtray in c_hallwy}
     {A Radio}                  c_balcny,
     {A Pocket Knife}           nowhere,   {given by bum}
     {AdventureBoy Magazine}    nowhere,   {found in rack in d_phrmcy}
     {A Rubber}                 d_phrmcy,
     {A Bottle of Wine}         nowhere,   {bought in disco, ordered by phone}
     {A Wallet}                 youhavit,
     {An Inflatable Doll}       nowhere,   {in closet in p_livrom}
     {An Apple}                 nowhere,   {on tree grown in p_garden}
     {A Pitcher}                nowhere,   {in cabinet in p_kitchn}
     {A Stool}                  p_garden,
     {A Rope}                   nowhere,   {innocent girl ties you with it}
     {A Display Rack}           d_phrmcy,
     {A Mushroom}               p_garden,
     {A Remote Control Unit}    nowhere,   {given by businessman}
     {A Curtain}                b_bar,
     {Water}                    nowhere,   {Can get it by Water On}
     {A Taxi}                   nowhere,   {Used in Hail taxi}
     {Inventory}                nowhere,   {Used in Take Inventory}
     {All}                      nowhere,   {Used in Take All, Drop All}
     {On, Off}              nowhere, nowhere, {Used in Water On, Water Off}
     {You}                      nowhere,
     {No object}                nowhere
         );

 verb_name : array[verbs] of word_name_string
      = ( 'GO  ', 'HAIL', 'TAKE', 'DROP', 'LOOK',
          'FLUS', 'OPEN', 'INFL', 'PLAY', 'PRES',
          'ENTE', 'EAT ', 'DRIN', 'BUY ', 'CLIM',
          'WATE', 'FILL', 'POUR', 'LIST', 'CLOS',
          'JUMP', 'MARR', 'FUCK', 'WEAR', 'ANSW',
          'CALL', 'BREA', 'CUT ', 'DANC', 'KILL',
          'PAY ', 'SMOK', 'SHOW', 'SMEL', 'HELP',
          'KISS', 'STAB', 'SAY ', 'QUIT',
          'SCOR', 'SAVE', 'REST', '' );

 obj_name : array[objects] of word_name_string
      = ( 'DESK', 'WASH', 'GRAF', 'MIRR', 'TOIL',
          'BUSI', 'BUTT', 'BART', 'DUDE', 'HOOK',
          'BILL', 'PREA', 'TV  ', 'SLOT', 'CARD',
          'ASHT', 'VOLU', 'BED ', 'BUM ', 'HOLE',
          'DOOR', 'WAIT', 'TABL', 'TELE', 'CLOS',
          'SINK', 'ELEV', 'DEAL', 'CABI', 'BUSH',
          'TREE', 'WIND', 'SIGN', 'GIRL', 'NEWS',
          'RING', 'WHIS', 'BEER', 'HAMM', 'GARB',
          'FLOW', 'CORE', 'SEED', 'CAND', 'PILL',
          'PLAN', 'PASS', 'RADI', 'KNIF', 'MAGA',
          'RUBB', 'WINE', 'WALL', 'DOLL', 'APPL',
          'PITC', 'STOO', 'ROPE', 'RACK', 'MUSH',
          'CONT', 'CURT', 'WATE',
          'TAXI', 'INVE', 'ALL ', 'ON  ', 'OFF ',
          'YOU ', ''
         );


 syn_verbs = 20;

 syn_verb : array[1..syn_verbs] of synonym
      = ( ( orig:'GET ';  repl:'TAKE' ),
          ( orig:'GRAB'; repl:'TAKE' ),
          ( orig:'LEAV'; repl:'DROP' ),
          ( orig:'PLAN'; repl:'DROP' ),
          ( orig:'GIVE'; repl:'DROP' ),
          ( orig:'SEAR'; repl:'LOOK' ),
          ( orig:'EXAM'; repl:'LOOK' ),
          ( orig:'READ'; repl:'LOOK' ),
          ( orig:'WATC'; repl:'LOOK' ),
          ( orig:'PULL'; repl:'OPEN' ),
          ( orig:'PUSH'; repl:'PRES' ),
          ( orig:'ORDE'; repl:'BUY ' ),
          ( orig:'SEDU'; repl:'FUCK' ),
          ( orig:'RAPE'; repl:'FUCK' ),
          ( orig:'SCRE'; repl:'FUCK' ),
          ( orig:'USE '; repl:'WEAR' ),
          ( orig:'DIAL'; repl:'CALL' ),
          ( orig:'SMAS'; repl:'BREA' ),
          ( orig:'STOP'; repl:'QUIT' ),
          ( orig:'BYE '; repl:'QUIT' )
         );


 syn_nouns = 17;

 syn_noun : array[1..syn_nouns] of synonym
      = ( ( orig:'CAB '; repl:'TAXI'),
          ( orig:'PEEP'; repl:'HOLE'),
          ( orig:'DRAW'; repl:'DESK'),
          ( orig:'BASI'; repl:'WASH'),
          ( orig:'PIMP'; repl:'DUDE'),
          ( orig:'MACH'; repl:'SLOT'),
          ( orig:'21  '; repl:'CARD'),
          ( orig:'BLAC'; repl:'CARD'),
          ( orig:'DISP'; repl:'RACK'),
          ( orig:'PHON'; repl:'TELE'),
          ( orig:'WEDD'; repl:'RING'),
          ( orig:'BLON'; repl:'VOLU'),
          ( orig:'EVE '; repl:'GIRL'),
          ( orig:'PAPE'; repl:'NEWS'),
          ( orig:'SHOT'; repl:'WHIS'),
          ( orig:'TRAS'; repl:'GARB'),
          ( orig:'UNIT'; repl:'CONT')
         );


gl_words = 9;

glue_words : array[1..gl_words] of word_name_string
      = ( 'A   ', 'AN  ', 'THE ', 'THIS', 'THAT',
          'AT  ', 'TO  ', 'FROM', 'WITH'  );

dir_name : array[directions] of word_name_string
      = ( 'NORT', 'SOUT', 'EAST', 'WEST', 'UP  ', 'DOWN', '' );

place_name : array[places] of place_name_string
      = ( 'I''m in a Hallway',
          'I''m in a Bathroom',
          'I''m in a Sleazy Bar',
          'I''m on a Street outside the Bar',
          'I''m in the Backroom',
          'I''m in a Filthy Dumpster',
          'I''m inside the room I broke into!',
          'I''m on a Window Ledge',
          'I''m in a Hooker''s Bedroom',
          'I''m on a Hooker''s Balcony',
          'I''m on a Downtown Street',
          'I''m in a Quickie Marriage Center',
          'I''m in the Main Casino Room',
          'I''m in the ''21'' Room',
          'I''m in the Lobby of the Hotel',
          'I''m in the Honeymoon Suite',
          'I''m in the Hotel Hallway',
          'I''m on the Honeymooner''s Balcony',
          'I''m at the Hotel Desk',
          'I''m in a Telephone Booth',
          'I''m in the Disco',
          'I''m on a Residential Street',
          'I''m in the Disco''s Entrance',
          'I''m in the Pharmacy',
          'I''m in the Penthouse Foyer',
          'I''m in the Jacuzzi',
          'I''m in the Kitchen',
          'I''m in the Garden',
          'I''m in the Living Room',
          'I''m on the Penthouse Porch',
          'Nowhere',
          'Carried by You'
        );

orig_path: path_array = (

{ Place Path to   North     South     East      West      Up        Down    }

                    (* ==================== BAR =================== *)
{b_hallwy}   (   b_bathrm, nowhere,  b_bar,    nowhere,  nowhere,  nowhere  ),
{b_bathrm}   (   nowhere,  b_hallwy, nowhere,  nowhere,  nowhere,  nowhere  ),
{b_bar}      (   b_street, nowhere,  nowhere,  b_hallwy, nowhere,  nowhere  ),
{b_street}   (   nowhere,  b_bar,    nowhere,  nowhere,  nowhere,  nowhere  ),
{b_backrm}   (   nowhere,  nowhere,  nowhere,  b_bar,    b_bedrm,  nowhere  ),
{b_g_dump}   (   nowhere,  nowhere,  nowhere,  b_street, nowhere,  nowhere  ),
{b_inroom}   (   b_wledge, nowhere,  nowhere,  nowhere,  nowhere,  nowhere  ),
{b_wledge}   (   nowhere,  nowhere,  b_balcny, nowhere,  nowhere,  nowhere  ),
{b_bedrm}    (   b_balcny, nowhere,  nowhere,  nowhere,  nowhere,  b_backrm ),
{b_balcny}   (   nowhere,  b_bedrm,  nowhere,  b_wledge, nowhere,  b_g_dump ),
                    (* =================== CASINO ================= *)
{c_street}   (   c_marryc, nowhere,  c_casino, nowhere,  nowhere,  nowhere  ),
{c_marryc}   (   nowhere,  c_street, nowhere,  nowhere,  nowhere,  nowhere  ),
{c_casino}   (   c_21room, nowhere,  c_lobby,  c_street, nowhere,  nowhere  ),
{c_21room}   (   nowhere,  c_casino, nowhere,  nowhere,  nowhere,  nowhere  ),
{c_lobby}    (   nowhere,  nowhere,  nowhere,  c_casino, c_htdesk, nowhere  ),
{c_hmoons}   (   c_hallwy, nowhere,  c_balcny, nowhere,  nowhere,  nowhere  ),
{c_hallwy}   (   nowhere,  nowhere,  c_htdesk, nowhere,  nowhere,  nowhere  ),
{c_balcny}   (   nowhere,  nowhere,  nowhere,  c_hmoons, nowhere,  nowhere  ),
{c_htdesk}   (   nowhere,  nowhere,  nowhere,  c_hallwy, nowhere,  c_lobby  ),
                    (* =================== DISCO ================== *)
{d_telbth}   (   d_disco,  nowhere,  nowhere,  nowhere,  nowhere,  nowhere  ),
{d_disco}    (   nowhere,  d_telbth, d_entrnc, nowhere,  nowhere,  nowhere  ),
{d_street}   (   d_entrnc, nowhere,  d_phrmcy, nowhere,  nowhere,  nowhere  ),
{d_entrnc}   (   nowhere,  d_street, nowhere,  nowhere,  nowhere,  nowhere  ),
{d_phrmcy}   (   nowhere,  nowhere,  nowhere,  d_street, nowhere,  nowhere  ),
                    (* ================= PENTHOUSE ================ *)
{p_pntfoy}   (   nowhere,  nowhere,  p_kitchn, nowhere,  p_livrom, nowhere  ),
{p_jacuzi}   (   nowhere,  nowhere,  nowhere,  nowhere,  p_pntpch, nowhere  ),
{p_kitchn}   (   nowhere,  nowhere,  nowhere,  p_pntfoy, nowhere,  nowhere  ),
{p_garden}   (   nowhere,  nowhere,  nowhere,  nowhere,  nowhere,  nowhere  ),
{p_livrom}   (   p_pntpch, nowhere,  nowhere,  nowhere,  nowhere,  p_pntfoy ),
{p_pntpch}   (   nowhere,  p_livrom, nowhere,  nowhere,  nowhere,  p_jacuzi ),
                    (* ================= ELSEWHERE ================ *)
{youhavit}   (   nowhere,  nowhere,  nowhere,  nowhere,  nowhere,  nowhere  ),
{nowhere}    (   nowhere,  nowhere,  nowhere,  nowhere,  nowhere,  nowhere  )
          );




type gamepos = record
                 first_var            : byte;
                 object_place         : array[objects] of places;
                 place_visited        : array[places] of boolean;
                 path                 : path_array;
                 your_place,
                 new_place            : places;
                 inven                : array[1..max_carried] of objects;
                 carrying             : 1..max_carried;
                 noun                 : objects;
                 verb                 : verbs;
                 direction            : directions;
                 command              : command_string;
                 verbnam,
                 objnam               : word_name_string;
                 game_ended           : boolean;
                 yesno                : char;
                 objects_carried,
                 money,
                 score,
                 TV_channel           : integer;
                 rope_in_use,
                 window_broken,
                 toilet_flushed,
                 called_555_0987,
                 called_555_6969,
                 called_555_0439,
                 rubber_worn,
                 hooker_fucked,
                 door_W_open,
                 radio_listened,
                 wine_ordered,
                 telephone_ringing,
                 telephone_answered,
                 hole_peeped,
                 girl_2_fucked,
                 tied_to_bed,
                 drawer_open,
                 closet_open,
                 cabinet_open,
                 doll_inflated,
                 stool_climbed,
                 water_on,
                 pitcher_full,
                 seeds_planted,
                 seeds_watered,
                 apple_given,
                 candy_given,
                 flowers_given,
                 ring_given,
                 married_to_girl      : boolean;
                 girl_name,
                 girl_part,
                 girl_do,
                 your_part,
                 your_object,
                 rubber_color,
                 rubber_flavor,
                 rubber_lubricated,
                 rubber_ribbed        : str15
               end;

 var    game_position        : gamepos;
        i                    : integer;
        p                    : integer;
        iores                : integer;
        line_from_kbd        : str120;
        verb_only,
        no_verb,
        no_object,
        no_direction         : boolean;
        full_verb,
        full_noun            : str25;
        save_file            : file of gamepos;
        taxi_destination     : str10;
        password             : str10;
        _noun                : objects;    {loop variable}
        anything_carried     : boolean;
