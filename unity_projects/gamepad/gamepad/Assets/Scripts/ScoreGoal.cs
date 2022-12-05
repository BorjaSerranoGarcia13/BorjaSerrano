using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreGoal : MonoBehaviour
{
    scoreCounter script;
    public int nPlayer;
    // Start is called before the first frame update
    void Start()
    {
      script = GameObject.Find("ScoreManager").GetComponent<scoreCounter>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    void OnTriggerEnter(Collider hit)
    {
       if (hit.gameObject.tag == "Ball")
       {
         script.StartFire();
         ball script2 = GameObject.Find("Ball").GetComponent<ball>();
         script2.playerBall = 0;
         switch(nPlayer)
         {
           case 1: script.scorePlayer1 += 1; break;
           case 2: script.scorePlayer2 += 1; break;
         }
       }
    }
}
