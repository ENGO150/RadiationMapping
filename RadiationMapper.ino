#define INPUT_PIN D6 //VIN PIN FOR GEIGER COUNTER
#define MEASUREMENT_TIME_MS 60000 //MINUTE
#define MAX_CPM 5000 //HOW MANY COUNTS TO STORE

unsigned long counts[MAX_CPM];
int last_index = -1;

//CALLBACK WHEN RADIATION PARTICLE IS DETECTED
void IRAM_ATTR increment_counts()
{
    counts[(++last_index) % MAX_CPM] = millis();
}

void setup()
{
    //INIT counts
    for (int i = 0; i < MAX_CPM; i++) counts[i] = 0;

    Serial.begin(9600);

    //INIT PINS
    pinMode(INPUT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INPUT_PIN), increment_counts, FALLING);
}

int last_counts = -1;
void loop()
{
    unsigned long current_millis = millis();
    int current_counts = 0;

    //COUNT
    for (int i = 0; i < MAX_CPM; i++)
    {
        if (counts[i] == 0) continue;
        if (current_millis - counts[i] >= MEASUREMENT_TIME_MS) //REMOVE COUNTS OLDER THAN MEASUREMENT_TIME_MS
        {
            counts[i] = 0;
            continue;
        }

        current_counts++; //COUNT RECENT
    }

    if (last_counts != current_counts) //PRINT CPM IF CHANGED
    {
        last_counts = current_counts;
        Serial.println(String(current_counts) + " CPM");
    }
}
