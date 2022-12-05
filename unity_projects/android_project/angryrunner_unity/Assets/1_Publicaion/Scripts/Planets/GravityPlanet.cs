using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GravityPlanet : MonoBehaviour
{
    CharacterController player;

    public float range = 5.0f;
    public float forceGravity;
    public Color color;

    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
    }

    void FixedUpdate() // Fixed para fisicas
    {
        if ((transform.position - player.transform.position).magnitude <= range)
        {
            Vector3 directionGravity = (player.transform.position - transform.position).normalized;
            Vector3 directionObject = player.transform.up;
            player.Move(-directionGravity * forceGravity * Time.deltaTime);
            Quaternion rotation = Quaternion.FromToRotation(directionObject, directionGravity) * player.transform.rotation;
            player.transform.rotation = Quaternion.Slerp(player.transform.rotation, rotation, 50 * Time.deltaTime);
        }
    }

    void OnDrawGizmosSelected()
    {
        Gizmos.color = color;
        Vector3 v = new Vector3(0.0f, 0.0f, 0.0f);
        Gizmos.DrawSphere(v, range);
    }

}
