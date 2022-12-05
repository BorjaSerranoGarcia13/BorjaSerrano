using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BalaBill : MonoBehaviour
{
    float destroy_time = 10.0f;
    bool destroy_enemy = false;

    Vector3 actualPosition;
    Vector3 newPosition;
    Vector3 vDirection = new Vector3(1, 0);

    public float speed = 2.0f;

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(ITimeGeneration());
    }

    // Update is called once per frame
    void Update()
    {
      if (destroy_enemy)
      {
        Destroy(gameObject);
      }

      transform.position += vDirection.normalized * speed * Time.deltaTime;
    }

    private void OnTriggerEnter(Collider other)
    {
        Destroy(gameObject);
    }

    IEnumerator ITimeGeneration()
    {
        destroy_enemy = false;
        yield return new WaitForSeconds(destroy_time);
        destroy_enemy = true;
    }
}
