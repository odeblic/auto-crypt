/*

begin:

[ALICE] data_A = random()
[ALICE] key_A = random()
[ALICE] expected_key_B = random()

[BOB] data_B = random()
[BOB] key_B = random()
[BOB] expected_key_A = random()

[ALICE] secret_A = encrypt(data_A, key_A)
[ALICE] send secret_A

[BOB] secret_B = encrypt(data_B, key_B)
[BOB] send secret_B

[ALICE] receive secret_B
[ALICE] expected_data_B = decrypt(secret_B, expected_key_B)
[ALICE] over_secret_B = encrypt(expected_data_B, key_A)

[BOB] receive secret_A
[BOB] expected_data_A = decrypt(secret_A, expected_key_A)
[BOB] over_secret_A = encrypt(expected_data_A, key_B)

[ALICE] receive over_secret_A
[ALICE] check over_secret_A = data_A
[ALICE] either key are OK, or try again

[BOB] receive over_secret_B
[BOB] check over_secret_B = data_B
[BOB] either key are OK, or try again


method :
send complicated encryption with the complete key
receive encryption with a PART of the key

method:
use of rolling randomized key
continuous adapting

method:
use hash before sending on network
to avoid key deduction by third party

method:
additional password can improve the security



initial state
  gotcha
    gotcha -> known by other : keyA, keyB
    uh ?   -> known by other : keyA
  uh ?
    gotcha -> known by other : keyB
    uh ?   -> known by other : none

stream of messages :
begin hash(key)
continue hash(last msg)
continue hash(last msg)
continue hash(last msg)
end hash(last msg)
send/receive data

one process for one direction
another process for the other direction
otherwise we can detect when the process is over

*/

class Agent
{
  public:

  bool first()
  {
    return true;
  }

  void process()
  {
    const short key = random();

    short data;
    short secret;
    short hash_secret;

    short expected_foreign_key;
    short over_secret;
    short foreign_key;

    do
    {
      data = random();
      secret = encrypt(data, key);
      hash_secret = hash(secret);

      send(hash_secret);
      over_secret = receive();
      expected_foreign_key = random();
    }
    while(over_secret != hash(encrypt(hash_secret, expected_foreign_key)));

    foreign_key = expected_foreign_key;
  }

  void send(short) {}
  short receive() { return 0; }

  short encrypt(short, short) { return 0; }
  short decrypt(short, short) { return 0; }

  short random() { return 0; }

  short hash(short) { return 0; }

  private:

  //short keys[16];
};

