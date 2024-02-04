#define IBUS_BUFFSIZE 32
#define IBUS_MAXCHANNELS 10

static uint8_t ibusIndex = 0;
static uint8_t ibus[IBUS_BUFFSIZE] = {0};
static uint16_t rcValue[IBUS_MAXCHANNELS];
static boolean rxFrameDone;

int channelWidths[IBUS_MAXCHANNELS];

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop()
{
  readRx();
}

void readRx()
{
  rxFrameDone = false;

  if (Serial1.available())
  {
    uint8_t val = Serial1.read();

    // Look for 0x2040 as start of packet
    if (ibusIndex == 0 && val != 0x20)
    {
      ibusIndex = 0;
      return;
    }
    if (ibusIndex == 1 && val != 0x40)
    {
      ibusIndex = 0;
      return;
    }

    if (ibusIndex == IBUS_BUFFSIZE)
    {
      ibusIndex = 0;
      int high = 3;
      int low = 2;

      for (int i = 0; i < IBUS_MAXCHANNELS; i++)
      {
        rcValue[i] = (ibus[high] << 8) + ibus[low];
        high += 2;
        low += 2;
      }

      for (int i = 0; i < IBUS_MAXCHANNELS; i++)
      {
        channelWidths[i] = map(rcValue[i], 1000, 2000, 1000, 2000);
        Serial.print(channelWidths[i]);
        Serial.print("     ");
      }

      Serial.println();

      rxFrameDone = true;
      return;
    }
    else
    {
      ibus[ibusIndex] = val;
      ibusIndex++;
    }
  }
}
