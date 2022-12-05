using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RedCoin : MonoBehaviour
{
    float rotation = 10.0f;
    float destroy_time = 10.0f;
    bool generation = false;

    private void Start()
    {
         StartCoroutine(ITimeGeneration());
    }

    void Update()
    {
       
        transform.Rotate(0.0f, rotation, 0.0f, Space.World);

        if (generation)
        {
            Destroy(gameObject);
            StopCoroutine(ITimeGeneration());
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "player")
        {
            Destroy(gameObject);
        }
    }

    IEnumerator ITimeGeneration()
    {
        generation = false;
        yield return new WaitForSeconds(destroy_time);
        generation = true;
    }
}
