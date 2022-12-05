using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowBatObject : MonoBehaviour
{
    private float randomY;
    private Vector3 ini;
    public float maxY = 0.0f,
                minY = 0.0f;
    float time_;

    bool doSomething = false;
    // Start is called before the first frame update
    void Start()
    {
      ini = transform.position;
      time_ = 1.0f;
      StartCoroutine(WaitForMove(time_));
    }

    // Update is called once per frame
    void Update()
    {
      ini.x = transform.position.x;
      ini.z = transform.position.z;

      StartCoroutine(WaitForMove(time_));

      if (doSomething)
      {

        randomY = Random.Range(minY,maxY);
        if (transform.position.y + randomY > maxY ||
        transform.position.y + randomY < minY)
        {
          transform.position = ini;
        }
        transform.position += new Vector3(0.0f, randomY, 0.0f);
      }
      else
      {
        StartCoroutine(WaitForMove(time_));
      }

    }

    IEnumerator WaitForMove(float time)
    {
       //doSomething = true;
       if (doSomething) doSomething = false;
       else doSomething = true;

        yield return new WaitForSeconds(time);

        //doSomething = false;
        if (doSomething) doSomething = false;
        else doSomething = true;
    }
}
