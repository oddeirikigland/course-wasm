import * as THREE from "../three.js";

const vertexShader = `
    varying vec3 distanceVec; 
    uniform vec3 distance_position;
    varying float roof;
    
    void main() {
      distanceVec = position - distance_position; 
      vec4 modelViewPosition = modelViewMatrix * vec4(position, 1.0);
      roof = abs(normal.z) > 0.001 ? 1.0 : 0.0 ;
      gl_Position = projectionMatrix * modelViewPosition; 
    }
  `


const fragmentShader = `
      varying vec3 distanceVec;
      varying float roof;

      void main() {
        float distance_squared = distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y + distanceVec.z * distanceVec.z;
        float distance = pow(distance_squared, 0.5);
        if (roof > 0.0) {
            gl_FragColor = vec4(1.0, 1.0,1.0, 1.0);
        } else {   
            float scaled_distance = distance / 100.;
            gl_FragColor = vec4(
                scaled_distance,
                scaled_distance,
                scaled_distance,
                1.0
            );
        }
      }
  `

export function createCustomMaterial(geometry, bus_stop_position) {
    let uniforms = {}
    uniforms.distance_position = {type: 'vec3', value: new THREE.Vector3(...bus_stop_position)}

    return new THREE.ShaderMaterial({
        uniforms: uniforms,
        fragmentShader: fragmentShader,
        vertexShader: vertexShader,
    })
}