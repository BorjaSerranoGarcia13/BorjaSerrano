using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PowerUps : MonoBehaviour
{

    private int eventNumber = 0;

    private int chose_power = 0;

    public GameObject power_up;
    public GameObject power_up_bad;

    public 

    // Start is called before the first frame update
    void Start()
    {
        InvokeRepeating("ChoseSpawn", 5.0f, 8.0f);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void ChoseSpawn()
    {
        chose_power = Random.Range(0, 2);
        eventNumber = 0;

        if(chose_power == 1)
        {
            eventNumber = Random.Range(0, 9);

            switch (eventNumber)
            {
                case 0: power_up.transform.position = new Vector3(6.55f, 0.55f, -6.84f); break;
                case 1: power_up.transform.position = new Vector3(4.33f, 0.55f, -1.57f); break;
                case 2: power_up.transform.position = new Vector3(6.55f, 0.55f, 2.86f); break;
                case 3: power_up.transform.position = new Vector3(-0.07f, 0.55f, 3.31f); break;
                case 4: power_up.transform.position = new Vector3(-0.07f, 0.55f, -1.82f); break;
                case 5: power_up.transform.position = new Vector3(-0.07f, 0.55f, -6.69f); break;
                case 6: power_up.transform.position = new Vector3(-4.48f, 0.55f, -1.68f); break;
                case 7: power_up.transform.position = new Vector3(-7.23f, 0.55f, -6.97f); break;
                case 8: power_up.transform.position = new Vector3(-7.23f, 0.55f, 3.28f); break;
            }
        }

        if (chose_power == 0)
        {
            eventNumber = Random.Range(0, 9);

            switch (eventNumber)
            {
                case 0: power_up_bad.transform.position = new Vector3(6.55f, 0.55f, -6.84f); break;
                case 1: power_up_bad.transform.position = new Vector3(4.33f, 0.55f, -1.57f); break;
                case 2: power_up_bad.transform.position = new Vector3(6.55f, 0.55f, 2.86f); break;
                case 3: power_up_bad.transform.position = new Vector3(-0.07f, 0.55f, 3.31f); break;
                case 4: power_up_bad.transform.position = new Vector3(-0.07f, 0.55f, -1.82f); break;
                case 5: power_up_bad.transform.position = new Vector3(-0.07f, 0.55f, -6.69f); break;
                case 6: power_up_bad.transform.position = new Vector3(-4.48f, 0.55f, -1.68f); break;
                case 7: power_up_bad.transform.position = new Vector3(-7.23f, 0.55f, -6.97f); break;
                case 8: power_up_bad.transform.position = new Vector3(-7.23f, 0.55f, 3.28f); break;
            }
        }

    }
}
