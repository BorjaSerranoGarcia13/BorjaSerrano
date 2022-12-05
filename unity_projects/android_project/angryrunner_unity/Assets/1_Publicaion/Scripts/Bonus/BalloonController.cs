using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BalloonController : MonoBehaviour
{
    public GameObject balloon;
    bool generation;

    public Text bonus;
    public Text count;
    public Text score;
    public Text timeCount;
    float timeOut = 3f;
    bool start = false;

    float speed_generation;
    
    public static int total_score;

    void Start()
    {
        speed_generation = 2.0f;
        generation = true;
        total_score = 0;
        bonus.text = "BONUS";
    }

    // Update is called once per frame
    void Update()
    {
        
        if (start == false)
        {
            if (timeOut <= 2)
            {
                count.text = "STARTS IN " + (timeOut + 1).ToString("f0");
            }
            
            if(timeOut <= 0)
            {
                start = true;
                timeOut = 30.0f;
            } 
        }
        else
        {
            count.text = ""; 
            if (timeOut >= 0) 
            {
                timeCount.text = "TIME " + timeOut.ToString("f0"); 
            }
            score.text = "SCORE " + total_score.ToString("f0");  
            if (timeOut <= 4.0f) 
            {
                generation = false;
            }
            
            if (generation == true)
            {
                StartCoroutine(ITimeGeneration());
                CreateBalloon();            
            }  
        }        
        if (timeOut < -3.0f)
        {
            timeCount.text = "";
            score.text = "";
            bonus.text = "";
            count.text = " SCORE " + total_score.ToString("f0");
        } 
        else if (timeOut < -6.0f)
        {
            Debug.Log("change scene");
        }
        
        if (timeOut > -9.0f)
        {
           timeOut -= Time.deltaTime; 
        }
    }

    void CreateBalloon()
    {
        Instantiate(balloon, transform);                
    }

    IEnumerator ITimeGeneration()
    {
        generation = false;
        yield return new WaitForSeconds(speed_generation);
        generation = true;
        if (speed_generation > 0.25f) speed_generation -= 0.15f;
    }
}
