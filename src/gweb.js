class gwebScriptTag extends HTMLElement {
  constructor() {
    super();
  }
  connectedCallback() {
    console.log(`
      <gweb-script> tag detected with content
      ${this.innerHTML}
      The JS version is currently not available.
    `);
  }
}
customElements.define("gweb-script", gwebScriptTag);
