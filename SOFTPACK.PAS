{$C+}
{$R+}
{$U+}

program PACK;

const  recsize      = 450;
       EOL          = #$0D;
       infile_name  = 'SOFTPORN.TXT';
       outfile_name = 'SOFTPORN.MSG';

type   rectype = array[1..recsize] of char;
       str     = string[120];

var line    : str;
    rec     : rectype;
    infile  : text;
    outfile : file of rectype;
    i       : integer;
    recpos  : integer;



procedure clearrec;
var i : integer;
begin
  recpos := 1;
  for i:=1 to recsize do
    rec[i] := chr(0);
end;


procedure addrec( c : char);
begin
  if recpos>recsize then
    begin
      writeln('Record overflow in :');
      writeln(line);
      halt;
    end;
  rec[recpos] := c;
  recpos := recpos + 1;
end;


procedure dumprec;
begin
  if recpos>1 then
    begin
      write( outfile, rec );
      write( recpos:4 );
    end;
  clearrec;
end;


begin  { Main program }

  writeln('Converting ',infile_name,' to ',outfile_name,'. Recsize=',recsize);
  writeln;

  assign(infile,infile_name);
  assign(outfile,outfile_name);

  reset(infile);
  rewrite(outfile);

  clearrec;

  randomize;

  while not eof(infile) do
    begin
      readln( infile, line );
      if copy(line,1,3)='###' then
        dumprec
      else if line<>'' then
        begin
          for i:=1 to length(line) do
            addrec(succ(line[i]));
          addrec(EOL);
        end;
    end;

  dumprec;

  close(infile);
  close(outfile);
  writeln;

end.
