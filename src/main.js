import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";
import * as Solver from "./solver/solver.js";

const site = generate();

Visualize.init(site);
Solver.init(site).then(res => setInterval(res.iterate, 1000))

